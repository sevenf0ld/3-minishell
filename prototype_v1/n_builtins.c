/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2023/12/29 18:21:49 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	n_builtins_3(char *path_str)
{
	if (!access(path_str, F_OK))
		return (1);
	else if (path_str[0] == '/')
	{
		printf("minishell: %s: No such file of directory\n", path_str);
		return (-1);
	}
	/*
	if (path_str[0] == '.' && path_str[1] == '/')
	{
		if (!access(path_str, X_OK))
		{
			char **test = malloc(sizeof(char *) * 2);
			test[0] = malloc(sizeof(char) * ft_strlen(path_str + 1));
			test[0] = path_str + 2;
			printf("check test[0]: %s\n", test[0]);
			test[1] = NULL;
			return (1);
			execve(path_str, test, NULL);
			printf("CAN EXECUTE\n");
			system(path_str);
		}
		else
		{
			if (access(path_str, F_OK) != 0)
			{
				printf("minishell: %s: No such file or directory\n", path_str);
				return (127);
			}
			else
			{
				printf("minishell: %s: Permission denied\n", path_str);
				return (126);
			}
		}
	}
	else if (!access(path_str, X_OK))
	{
		printf("PATH STR EXISTS\n");
		return (1);
	}
	else if (path_str[0] == '/')
	{
		printf("minishell: %s: No such file of directory\n", path_str);
		return (-1);
	}
	else
		printf("IT IS RELATIVE\n");
	*/
	return (0);
}

void	n_builtins_2(t_command **a, char **input, char *cmd, t_status *stat)
{
	(void) cmd;
	pid_t		pid;
	t_command	*tmp;

	tmp = *a;
	pid = fork();
	if (pid == -1)
	{
		free(input);
		return ;
	}
	if (pid == 0)
	{
		if (!tmp->builtin)
			execve(input[0], input, NULL);
		//exit(127);
		stat->s_code = 127;
	}
	else
	{
		if (tmp->read_end != -1)
			close_err(tmp->read_end);
		if (tmp->write_end != -1)
			close_err(tmp->write_end);
		//free_2d_arr(input);
		cmd = NULL;
		int	wstat;
		int	got_pid;
		do
		{
			got_pid = wait(&wstat);
			if (got_pid == pid)
				break ;
			if (got_pid == -1)
			{
				perror("waitpid");
				return ;
			}
		}
		while (got_pid == wait(&wstat));
		if (WIFEXITED(wstat))
			stat->s_code = WEXITSTATUS(wstat);
		else if (WIFSIGNALED(wstat))
			stat->s_code = WTERMSIG(wstat);
		else if (WIFSTOPPED(wstat))
			stat->s_code = WIFSTOPPED(wstat);
	}
}

void	n_builtins_1(t_command **a, char *path_str, t_status *stat)
{
	t_command	*tmp;
	int			i;
	char		**input;

	tmp = *a;
	input = (char **)malloc_err((tmp->num_f + tmp->num_a + 2) * sizeof(char *));
	input[0] = path_str;
	input[tmp->num_f + tmp->num_a + 1] = NULL;
	i = -1;
	if (tmp->flags != NULL)
	{
		while (++i < tmp->num_f)
			input[i + 1] = tmp->flags[i];
	}
	i = -1;
	if (tmp->args != NULL)
	{
		while (++i < tmp->num_a)
			input[i + tmp->num_f + 1] = tmp->args[i];
	}
	n_builtins_2(a, input, tmp->cmd, stat);
	//n_builtins_2(a, input, path_str, stat);
	return ;
}

void	n_builtins(t_command **a, t_status *stat)
{
	int			i;
	int			j;
	t_command	*tmp;
	char		**path;
	char		*path_str;
	//bool		path_exists;

	tmp = *a;
	i = 0;
	j = n_builtins_3(tmp->cmd);
	path = NULL;
	path_str = NULL;
	//path_exists = true;
	if (j == 1)
	{
		path_str = tmp->cmd;
		if (tmp->cmd[0] == '.' && tmp->cmd[1] == '/')
		{
			path_str += 2;
		}
	}
	else if (j == 0)
	{
		if (tmp->builtin)
			return ;
		t_fixed	*ftmp;
		for (ftmp = tmp->env_var->fixed; ftmp != NULL; ftmp = ftmp->fnext)
		{
			if (!ft_strcmp("PATH", ftmp->fkey))
			{
				path = ft_split(ftmp->fvalue, ':');
				break ;
			}
		}
		//if (!path)
			//path_exists = false;
		if (ftmp == NULL)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(tmp->cmd, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			tmp->stat->s_code = 127;
			return ;
		}
		while (path[i])
		{
			path_str = ft_strjoin(path[i], "/");
			path_str = ft_strjoin(path_str, tmp->cmd);
			if (!access(path_str, F_OK))
				break ;
			i++;
		}
		if (!path[i])
		//if (!path[i] && path_exists)
		{
			printf("minishell: %s: command not found\n", tmp->cmd);
			tmp->stat->s_code = 127;
		}
		//else if (!path[i] && !path_exists)
			//printf("minishell: %s: No such file of directory\n", tmp->cmd);
	}
	else if (j == -1)
		return ;
	else if (j >= 100)
	{
		tmp->stat->s_code = j;
		return ;
	}
	n_builtins_1(a, path_str, stat);
	return ;
}
