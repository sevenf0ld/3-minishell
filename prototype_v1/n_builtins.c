/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2023/11/24 03:43:58 by maiman-m         ###   ########.fr       */
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
	return (0);
}


void	n_builtins_2(t_command **a, char **input, char *cmd)
{
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
		redirect_command_io(tmp);
		if (execve(input[0], input, NULL) == -1)
			fprintf(stdout, "\n>>> [%s] failed <<<\n", cmd);
	}
	else
	{
		wait(NULL);
		if (tmp->read_end != -1)
			close_err(tmp->read_end);
		if (tmp->write_end != -1)
			close_err(tmp->write_end);
		fprintf(stdout, "\n>>> [%s] success <<<\n", cmd);
		free_2d_arr(input);
	}
	return ;
}

void	n_builtins_1(t_command **a, char *path_str)
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
	n_builtins_2(a, input, tmp->cmd);
	return ;
}

void	n_builtins(t_command **a)
{
	int			i;
	int			j;
	t_command	*tmp;
	char		**path;
	char		*path_str;



	tmp = *a;
	i = 0;
	j = n_builtins_3(tmp->cmd);
	path = NULL;
	path_str = NULL;
	if (j == 1)
		path_str = tmp->cmd;
	else if (j == 0)
	{
		path = ft_split(getenv("PATH"), ':');
		/*
		if (tmp->builtin == false)
			path = ft_split(getenv("PATH"), ':');
		else
		{
			t_fixed	*ftmp;
			for (ftmp = tmp->env_var->fixed; ftmp != NULL; ftmp = ftmp->fnext)
			{
				if (!ft_strcmp("PATH", ftmp->fkey))
					break ;
			}
			fprintf(stderr, "FVALUE %s\n", ftmp->fvalue);
			path = ft_split(ftmp->fvalue, ':');
		}
		*/
		while (path[i])
		{
			//fprintf(stderr, "%i. %s\n", i, path[i]);
			path_str = ft_strjoin(path[i], "/");
			path_str = ft_strjoin(path_str, tmp->cmd);
			if (!access(path_str, F_OK))
				break ;
			i++;
		}
		if (!path[i])
			printf("minishell: %s: command not found\n", tmp->cmd);
	}
	else if (j == -1)
		return ;
	n_builtins_1(a, path_str);
	return ;
}
