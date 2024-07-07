/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:37:13 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 17:48:15 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*parse_equals(char *env)
{
	int		y;
	t_env	*env_data;
	int		flag;

	flag = 0;
	y = -1;
	env_data = malloc(sizeof(env_data));
	while (env[++y])
	{
		if (flag == 0 && env[y] == '=')
		{
			env_data->key = ft_substr(env, 0, y);
			flag = 1;
		}
		else if (flag == 1)
		{
			env_data->value = ft_substr(env, y, ft_strlen(env) - y);
			break ;
		}
	}
	return (env_data);
}

void	search_env(t_minishell *minishell, char *key)
{
	t_list	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (ft_strnstr(((t_env *)tmp->content)->key, key, ft_strlen(key)))
		{
			ft_printf("%s\n", ((t_env *)tmp->content)->value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	add_env(t_minishell *minishell, char *key, char *value)
{
	t_env	*env_data;
	t_list	*new;

	env_data = malloc(sizeof(env_data));
	env_data->key = key;
	env_data->value = value;
	new = ft_lstnew(env_data);
	ft_lstadd_back(&minishell->env, new);
}

void	print_env(t_minishell *minishell)
{
	t_list	*env_data;

	env_data = minishell->env;
	while (env_data)
	{
		ft_printf("%s=%s\n", ((t_env *)env_data->content)->key,
			((t_env *)env_data->content)->value);
		env_data = env_data->next;
	}
}

void	parse_env(t_minishell *minishell, char **env)
{
	int	i;

	i = 0;
	minishell->env = ft_lstnew(parse_equals(env[0]));
	while (env[++i])
		ft_lstadd_back(&minishell->env, ft_lstnew(parse_equals(env[i])));


	print_env(minishell);
}
