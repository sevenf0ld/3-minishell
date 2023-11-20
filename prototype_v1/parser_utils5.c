/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:26:35 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/21 00:19:13 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	redirect_io_file(int *fd_arr, char mode)
{
	int	i;

	i = 0;
	while (fd_arr[i] != INT_MIN)
		i++;
	if (mode == 'i')
		dup2_err(fd_arr[i - 1], STDIN_FILENO);
	else if (mode == 'o')
		dup2_err(fd_arr[i - 1], STDOUT_FILENO);
}

/*
 * if FIRST
 * ├ read from SI
 * └ write to pipe write_end[1]
 *
 * if LAST
 * ├ read from pipe read_end[0]
 * └ write to SO
 *
 * if IN BETWEEN
 * ├ read from pipe read_end[0]
 * └ write to pipe write_end[1]
 */
void	redirect_io_pipe(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	if (!cur)
		return ;
	if (cur->pos == 0)
	{
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
			dup2_err(cur->write_end, STDOUT_FILENO);
	}
	else if (cur->pos == cur->size - 1)
	{
		if (cur->std_in == NULL)
			dup2_err(cur->read_end, STDIN_FILENO);
	}
	else
	{
		if (cur->std_in == NULL)
			dup2_err(cur->read_end, STDIN_FILENO);
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
			dup2_err(cur->write_end, STDOUT_FILENO);
	}
}

/*
 * if NULL means no file redirection
 * 		read from pipe read_end[0]
 * 		write to pipe write_end[1]
 * else read from or write to file
 */
void	redirect_command_io(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	if (!cur)
		return ;
	if (cur->std_in != NULL)
		redirect_io_file(cur->std_in, 'i');
	if (cur->std_out_o != NULL || cur->std_out_a != NULL)
		redirect_io_file(cur->std_out_o, 'o');
	if (cur->size == 1)
		return ;
	redirect_io_pipe(cur);
}
