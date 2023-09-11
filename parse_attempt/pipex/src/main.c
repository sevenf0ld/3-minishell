/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:46:54 by maiman-m          #+#    #+#             */
/*   Updated: 2023/06/05 15:43:43 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	if (pipe(pipe_fd) == -1)
		report_err("Pipe");
	pid = fork();
	if (pid == -1)
		report_err("Fork");
	if (pid == 0)
		child_process(argv, envp, pipe_fd);
	wait(NULL);
	calling_process(argv, envp, pipe_fd, argc);
}
