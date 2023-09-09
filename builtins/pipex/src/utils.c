/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:33:26 by maiman-m          #+#    #+#             */
/*   Updated: 2023/06/07 16:15:27 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	report_err(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	close_err(int fd, char *err_msg)
{
	if (close(fd) == -1)
	{
		perror(err_msg);
		exit(EXIT_FAILURE);
	}
}

/*
 * PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
 * ---> /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
 * ---> "/usr/local/bin" "/usr/bin" "/bin" "/usr/sbin" "/sbin" "/usr/local/munki"
 */
char	**split_env(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	return (ft_split(*envp + 5, ':'));
}

void	free_in_out(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

/*
 * receives '<cmd> <flags>' and the environment path as its arguments
 * ---> "<cmd>" "<flags>" NULL
 * <cmd> is stored in prog_name
 * /usr/.../... ---> /usr/.../.../
 * /usr/.../.../ ---> /usr/.../.../<cmd>
 * check for file existence and execute permissions
 * if all is well and return value is 0, exit the loop
 * else keep iterating over each system path
 */
void	get_and_run_exe(char *cmd_w_flags, char **envp)
{
	char	**cmdl_args;
	char	**sys_paths;
	char	*env_path;
	char	*prog_path;

	cmdl_args = ft_split(cmd_w_flags, ' ');
	sys_paths = split_env(envp);
	while (*sys_paths)
	{
		env_path = ft_strjoin(*sys_paths, "/");
		prog_path = ft_strjoin(env_path, cmdl_args[0]);
		free(env_path);
		if (!access(prog_path, X_OK))
			break ;
		free(prog_path);
		sys_paths++;
	}
	if (!*sys_paths)
	{
		ft_putstr_fd("Command does not exist\n", 2);
		free_in_out(cmdl_args);
		exit(EXIT_FAILURE);
	}
	execve(prog_path, cmdl_args, envp);
	report_err("Execution");
}
