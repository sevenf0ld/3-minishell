/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2024/01/21 11:29:53 by maiman-m         ###   ########.fr       */
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

void	n_builtins_2(t_command **a, char **input, char *cmd, t_status *stat, t_command **cmds)
{
	(void) cmd;
        (void) input;
        (void) stat;
	pid_t		pid;
	t_command	*tmp;

	tmp = *a;
	pid = fork();
	if (pid == -1)
	{
		//free(input);
		return ;
	}
	if (pid == 0)
	{
                close_unused_ends(cmds, tmp->pos);
                redirect_command_io(*a);
		if (!tmp->builtin)
                {
			execve(input[0], input, NULL);
		        stat->s_code = 127;
                }
                else if (!ft_strcmp(tmp->cmd, "echo"))
                    b_echo(tmp);
                else if (!ft_strcmp(tmp->cmd, "pwd"))
                    b_pwd(tmp, 'w');
                else if (!ft_strcmp(tmp->cmd, "cd") && tmp->size > 1)
                    b_cd(tmp);
                else if (!ft_strcmp(tmp->cmd, "env"))
                    b_env(tmp, &(tmp->env_var->fixed));
                else if (!ft_strcmp(tmp->cmd, "unset"))
                    b_unset(tmp, &(tmp->env_var->fixed));
                else if (!ft_strcmp(tmp->cmd, "export") && tmp->size > 1)
                    b_export(tmp, &(tmp->env_var->fixed));
                else if (!ft_strcmp(tmp->cmd, "exit") && tmp->size > 1)
                    b_exit(tmp);
                exit(EXIT_SUCCESS);
	}
}


void	n_builtins_1(t_command **a, char *path_str, t_status *stat, t_command **cmds)
{
	t_command	*tmp;

	tmp = *a;
        tmp->args[0] = path_str;
	n_builtins_2(a, tmp->args, tmp->cmd, stat, cmds);
	return ;
}


void	n_builtins(t_command **a, t_status *stat, t_command **cmds)
{
	int			i;
	int			j;
	t_command	*tmp;
	char		**path;
	char		*path_str;
	//bool		path_exists;

	tmp = *a;
        if (!tmp->exec)
        {
            //if (tmp->write_end != -1)
            //    close_err(tmp->write_end, stat);
            //if (tmp->read_end != -1)
            //    close_err(tmp->read_end, stat);
            return ;
        }
	i = 0;
	j = n_builtins_3(tmp->cmd);
	path = NULL;
	path_str = NULL;
	//path_exists = true;
	if (j == 1)
	{
		path_str = tmp->cmd;
                /*
		if (tmp->cmd[0] == '.' && tmp->cmd[1] == '/')
		{
			path_str += 2;
		}
                */
	}
	else if (j == 0)
	{
		if (tmp->builtin)
                {
                        n_builtins_2(a, NULL, NULL, stat, cmds);
			return ;
                }
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
        /*
	else if (j >= 100)
	{
		tmp->stat->s_code = j;
		return ;
	}
        */
	n_builtins_1(a, path_str, stat, cmds);
	return ;
}
