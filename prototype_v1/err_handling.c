/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:00:50 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/03 11:24:53 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	report_err(char *fn, int flag, t_status *stat)
{
	if (flag == 1)
		perror(fn);
	else
		ft_putstr_fd(fn, 2);
	stat->s_code = 2;
}

void	*malloc_err(size_t size, t_status *stat)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		report_err("malloc", 1, stat);
	return (ret);
}

int	lim_err(char *file, int flags, mode_t mode, t_status *stat)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		report_err("open", 1, stat);
	return (fd);
}

int	open_err(char *file, int flags, mode_t mode, t_command *c_node)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
	{
		if (!c_node->exec)
			return (fd);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		report_err(file, 1, c_node->stat);
		c_node->exec = false;
                c_node->stat->s_code = 1;
	}
	return (fd);
}

void	dup2_err(int old_fd, int new_fd, t_status *stat)
{
	static int	i;

	i = 0;
	if (dup2(old_fd, new_fd) == -1)
	{
		report_err("dup2", 1, stat);
		fprintf(stderr, "dup error on nth attempt %i\n", i);
	}
	else
		i++;
}
