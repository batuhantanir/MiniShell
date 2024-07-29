/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:17:02 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/29 20:22:26 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	close_fd(t_minishell *minishell)
{
	int	i;

	i = -1;
	while (++i < minishell->pipe_count * 2)
		close(minishell->pipe_fd[i]);
	i = -1;
	while (++i < minishell->pipe_count + 1)
	{
		waitpid(minishell->pid[i], &minishell->exit_code, 0);
		minishell->exit_code = WEXITSTATUS(minishell->exit_code);
	}
	free(minishell->pipe_fd);
	free(minishell->pid);
	return (SUCCESS);
}

int	ft_pipe(t_minishell *minishell, char **cmd, char ***args)
{
	int	i;

	i = -1;
	if (create_pipe(minishell) == FAILURE)
		return (FAILURE);
	while (++i < minishell->pipe_count + 1)
	{
		minishell->pid[i] = fork();
		if (minishell->pid[i] == -1)
			return (FAILURE);
		else if (minishell->pid[i] == 0)
			pipe_fork(minishell, i, cmd, args);
	}
	return (close_fd(minishell));
}

int	multiple_command(t_minishell *minishell)
{
	char	**cmd;
	char	***args;
	int		a;
	int		b;

	args = minishell->args;
	cmd = ft_calloc(1, sizeof(char *) * (dlist_size(minishell->tokens) + 1));
	remove_quotes(args);
	a = 0;
	b = 0;
	while (args[a])
	{
		if (args[a][0])
		{
			cmd[b] = args[a][0];
			b++;
		}
		a++;
	}
	if (ft_pipe(minishell, cmd, args) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
