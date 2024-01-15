/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:00:50 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/15 10:55:52 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	report_err(char *fn, int flag, t_status *stat)
{
	if (flag == 1)
		perror(fn);
	else
		ft_putstr_fd(fn, 2);
        stat->s_code = 1;
}

void	*malloc_err(size_t size, t_status *stat)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		report_err("malloc", 1, stat);
	return (ret);
}

int	open_err(char *file, int flags, mode_t mode, t_command *c_node)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
        {
		report_err("open", 1, c_node->stat);
                c_node->exec = false;
        }
	return (fd);
}

void	dup2_err(int old_fd, int new_fd, t_status *stat)
{
        static int i = 0;
	if (dup2(old_fd, new_fd) == -1)
	{
		report_err("dup2", 1, stat);
		fprintf(stderr, "dup error on nth attempt %i\n", i);
	}
	else
		i++;
}

void	close_err(int fd, t_status *stat)
{
    static int i = 0;
	if (close(fd) == -1)
        {
		report_err("close", 1, stat);
                fprintf(stderr, "close error on nth attempt %i\n", i);
        }
        else
            i++;
}

void	quote_err(char *a, t_status *stat)
{
	report_err("minishell: unterminated quotes ", 0, stat);
	report_err(a, 0, stat);
	report_err((" \n"), 0, stat);
}

void	pipe_err(int *pipe_arr, t_status *stat)
{
	if (pipe(pipe_arr) == -1)
		report_err("pipe", 1, stat);
}

int	dup_err(int old_fd, t_status *stat)
{
	int	new_fd;

	new_fd = dup(old_fd);
	if (new_fd == -1)
		report_err("dup", 1, stat);
	return (new_fd);
}

void    redir_err(char *token, t_status *stat)
{
    report_err("minishell: syntax error near unexpected token `", 0, stat);
    if (!token)
        report_err("newline", 0, stat);
    else
        report_err(token, 0, stat);
    report_err("'\n", 0, stat);
}

void    symbols_err(t_status *stat)
{
    report_err("minishell: this is not required by the subject\n", 0, stat);
}

void    first_err(t_status *stat)
{
    report_err("minishell: syntax error near unexpected token `|'\n", 0, stat);
}
