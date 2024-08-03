/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:11:34 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 13:36:41 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <dirent.h>

void	ft_all_lower(char **str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
			(*str)[i] = (*str)[i] + 32;
}

int	check_builtin(t_minishell *minishell, char **cmd, char ***args, int *i)
{
	if (cmd[*i] == NULL)
		return (1);
	ft_all_lower(&cmd[*i]);
	if (ft_strcmp(cmd[*i], "env") == 0)
	{
		minishell->exit_code = 0;
		print_env(minishell);
	}
	else if (ft_strcmp(cmd[*i], "export") == 0)
	{
		export(minishell, (*args), i);
		if (minishell->exit_code != 1)
			minishell->exit_code = 0;
	}
	else if (ft_strcmp(cmd[*i], "pwd") == 0)
	{
		get_pwd();
		minishell->exit_code = 0;
	}
	else if (ft_strcmp(cmd[*i], "unset") == 0)
	{
		unset(minishell, (*args));
		minishell->exit_code = 0;
	}
	else if (ft_strcmp(cmd[*i], "cd") == 0)
	{
		cd(minishell, (*args)[1]);
		if (minishell->exit_code != 1)
			minishell->exit_code = 0;
	}
	else if (ft_strcmp(cmd[*i], "echo") == 0)
	{
		echo(args[*i]);
		minishell->exit_code = 0;
	}
	else if (ft_strcmp(cmd[*i], "exit") == 0)
	{
		ft_exit(minishell, (*args));
		minishell->exit_code = 0;
	}
	else
		return (0);
	reset_fd(minishell);
	if (args)
		free_args(args);
	return (1);
}

void	check_pid(pid_t *pid, t_minishell *minishell, char ***args, int *i)
{
	char	**envs;
	int		j;

	envs = env(minishell);
	j = 0;
	if ((*pid) == 0)
	{
		if (execve(minishell->path, (*args), envs) == -1)
		{
			if (!type_control(minishell, args, envs, i))
				exit(1);
			ft_putstr_fd("minishell: ", STDOUT_FILENO);
			ft_putstr_fd(minishell->path, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(127);
		}
	}
	else
	{
		waitpid((*pid), &minishell->exit_code, 0);
		minishell->exit_code = WEXITSTATUS(minishell->exit_code);
		reset_fd(minishell);
		free(envs);
		free_args(args);
	}
}

void	reset_fd(t_minishell *minishell)
{
	if (minishell->g_fd.change)
	{
		dup2(minishell->g_fd.std_out, STD_OUTPUT);
		dup2(minishell->g_fd.std_in, STD_INPUT);
		minishell->g_fd.change = 0;
	}
}

static void	arg_type(t_minishell *minishell, char *arg)
{
	DIR	*dir;

	dir = opendir(arg);
	if ((dir) != NULL)
	{
		closedir(dir);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		minishell->exit_code = 126;
	}
	else if (access(arg, F_OK) == -1)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		minishell->exit_code = 127;
	}
	else if (access(arg, X_OK) == -1)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		minishell->exit_code = 126;
	}
}

int	type_control(t_minishell *minishell, char ***args, char **envs, int *i)
{
	if (ft_strncmp((*args)[0], "./", 2) == 0 || ft_strncmp((*args)[0], "/",
			1) == 0)
		if (execve((*args)[0], args[*i], envs) == -1)
		{
			arg_type(minishell, (*args)[0]);
			if (minishell->sign)
				free(minishell->path);
			return (exit(minishell->exit_code), 0);
		}
	return (FAILURE);
}
