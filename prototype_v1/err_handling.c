/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:00:50 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/27 15:06:58 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	report_err(char *fn, int flag)
{
	if (flag == 1)
		perror(fn);
	else
		ft_putstr_fd(fn, 2);
}

void	*malloc_err(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		report_err("malloc", 1);
	return (ret);
}

int	open_err(char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		report_err("open", 1);
	return (fd);
}

void	dup2_err(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		report_err("dup2", 1);
}

void	close_err(int fd)
{
	if (close(fd) == -1)
		report_err("close", 1);
}

void	quote_err(void)
{
	report_err("error: unterminated quotes\n", 0);
}

void	pipe_err(int *pipe_arr)
{
	if (pipe(pipe_arr) == -1)
		report_err("pipe", 1);
}

int	dup_err(int old_fd)
{
	int	new_fd;

	new_fd = dup(old_fd);
	if (new_fd == -1)
		report_err("dup", 1);
	return (new_fd);
}
