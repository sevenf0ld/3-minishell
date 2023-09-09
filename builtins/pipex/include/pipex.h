/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:34:09 by maiman-m          #+#    #+#             */
/*   Updated: 2023/06/06 12:08:36 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

void	report_err(char *err_msg);
void	close_err(int fd, char *err_msg);
char	**split_env(char **envp);
void	free_in_out(char **arr);
void	get_and_run_exe(char *cmd_w_flags, char **envp);
void	child_process(char **argv, char **envp, int *pipe_fd);
void	calling_process(char **argv, char **envp, int *pipe_fd, int argc);

#endif
