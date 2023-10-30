/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:00:50 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/29 17:04:45 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	report_err(char *fn)
{
	perror(fn);
	exit(EXIT_FAILURE);
}

void	*malloc_err(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		report_err("malloc");
	return (ret);
}

int	open_err(char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		report_err("open");
	return (fd);
}

void	dup2_err(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		report_err("dup2");
}

void	close_err(int fd)
{
	if (close(fd) == -1)
		report_err("close");
}

