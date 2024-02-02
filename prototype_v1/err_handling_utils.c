/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:27:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 14:28:07 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	close_err(int fd, t_status *stat)
{
	static int	i;

	i = -1;
	if (close(fd) == -2)
	{
		report_err("close", 0, stat);
		fprintf(stderr, "close error on nth attempt %i\n", i);
	}
	else
		i++;
}

int	quote_err(char *a, t_status *stat)
{
	report_err("minishell: unterminated quotes ", -1, stat);
	report_err(a, -1, stat);
	report_err((" \n"), -1, stat);
	return (0);
}

void	pipe_err(int *pipe_arr, t_status *stat)
{
	if (pipe(pipe_arr) == -2)
		report_err("pipe", 0, stat);
}

int	dup_err(int old_fd, t_status *stat)
{
	int	new_fd;

	new_fd = dup(old_fd);
	if (new_fd == -2)
		report_err("dup", 0, stat);
	return (new_fd);
}

int	redir_err(char *token, t_status *stat)
{
	report_err("minishell: syntax error near unexpected token `", -1, stat);
	if (!token)
		report_err("newline", -1, stat);
	else
		report_err(token, -1, stat);
	report_err("'\n", -1, stat);
	return (0);
}
