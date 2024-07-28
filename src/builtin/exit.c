/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:48:47 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/28 19:49:19 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_str_digit(char *str)
{
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	free_minishell(t_minishell *mini)
{
	t_dlist	*tmp;

	while (mini->env)
	{
		tmp = mini->env;
		mini->env = mini->env->next;
		free(tmp->data);
		free(tmp);
	}
	free(mini->oldpwd);
	free(mini->line);
	while (mini->tokens)
	{
		tmp = mini->tokens;
		mini->tokens = mini->tokens->next;
		free(tmp->data);
		free(tmp);
	}
	free(mini);
}

static int	max_int(char *str)
{
	char	*number;

	if (str[0] == '-' || str[0] == '+')
		str++;
	number = ft_itoa(ft_atoi(str));
	if (ft_strcmp(number, str) != 0)
		return (free(number), 0);
	free(number);
	return (1);
}

static void	check_numeric(char *av, int *exit_code)
{
	if (is_str_digit(av) && max_int(av))
		(*exit_code) = ft_atoi(av);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		(*exit_code) = 255;
	}
}

void	ft_exit(t_minishell *mini, char **av)
{
	int	exit_code;
	int	i;

	i = 0;
	while (av[i])
		i++;
	exit_code = 0;
	ft_putstr_fd("exit\n", STD_OUTPUT);
	free_minishell(mini);
	if (i > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		exit_code = 1;
	}
	else if (av[1] != NULL)
		check_numeric(av[1], &exit_code);
	else
		exit_code = mini->exit_code;
	exit(exit_code);
}
