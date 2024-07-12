/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:37:13 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/12 14:44:37 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_key(char *line)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '=')
		j++;
	return (j);
}

char *get_value(char *line)
{
	int		i;
	char	*value;

	if (!line)
		return (NULL);
	i = get_key(line);
	if (!line[i])
		return (NULL);
	value = ft_strdup(line + i + 1);
	return (value);
}

t_dlist	*search_env(t_minishell *minishell, char *key)
{
	t_dlist	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, key, get_key(tmp->data)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_env(t_minishell *minishell)
{
	t_dlist	*env_data;

	env_data = minishell->env;
	while (env_data && ft_printf("%s\n", env_data->data))
		env_data = env_data->next;
}

void	parse_env(t_minishell *minishell, char **env)
{
	int	i;

	i = 0;
	minishell->env = dlist_new(strdup(env[i]));
	while (env[++i])
		dlist_add_back(&minishell->env, dlist_new(strdup(env[i])));
}
