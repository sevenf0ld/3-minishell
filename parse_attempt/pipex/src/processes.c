/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:08:05 by maiman-m          #+#    #+#             */
/*   Updated: 2023/06/07 16:19:40 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * close the read end
 * stdin points to the same file table entry as the infile
 * stdout points to the same file table entry as the write end
 * close the write end
 * execute
 */
void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		report_err("Infile");
	close_err(pipe_fd[0], "Child pipe read end");
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close_err(infile, "Infile");
		report_err("Child STDIN Redirection");
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close_err(pipe_fd[1], "Child pipe write end");
		report_err("Child STDOUT Redirection");
	}
	close_err(pipe_fd[1], "Child pipe write end");
	get_and_run_exe(argv[2], envp);
}

/*
 * overwrite a file so as to prevent corrupted files
 * with rwx permissions for the owner, the group and others
 * close the write end
 * stdout points to the same file table entry as the outfile
 * stdin points to the same file table entry as the read end
 * close the read end
 * execute
 */
void	calling_process(char **argv, char **envp, int *pipe_fd, int argc)
{
	int	outfile;

	outfile = open(argv[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfile == -1)
		report_err("Outfile");
	close_err(pipe_fd[1], "Parent pipe write end");
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close_err(outfile, "Outfile");
		report_err("Parent STDOUT Redirection");
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close_err(pipe_fd[0], "Parent pipe read end");
		report_err("Parent STDIN Redirection");
	}
	close_err(pipe_fd[0], "Parent pipe read end");
	get_and_run_exe(argv[3], envp);
}
