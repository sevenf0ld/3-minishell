/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:26:35 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 17:03:47 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	redirect_io_file(int *fd_arr, char mode, t_command *c_node)
{
	int	i;

	i = 0;
	while (fd_arr[i] != INT_MIN)
		i++;
	if (mode == 'i' && fd_arr[i - 1] != -1)
		dup2_err(fd_arr[i - 1], STDIN_FILENO, c_node->stat);
	else if (c_node->last_out != -1 && (mode == 'o' || mode == 'a'))
		dup2_err(c_node->last_out, STDOUT_FILENO, c_node->stat);
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
static void	redirect_io_pipe(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	if (!cur)
		return ;
	if (cur->pos == 0)
	{
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
			dup2_err(cur->write_end, STDOUT_FILENO, c_node->stat);
	}
	else if (cur->pos == cur->size - 1)
	{
		if (cur->std_in == NULL && cur->num_l == 0)
			dup2_err(cur->read_end, STDIN_FILENO, c_node->stat);
	}
	else
	{
		if (cur->std_in == NULL && cur->num_l == 0)
			dup2_err(cur->read_end, STDIN_FILENO, c_node->stat);
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
			dup2_err(cur->write_end, STDOUT_FILENO, c_node->stat);
	}
}

/*
 * calls redirect_io_file() if std* arrays are not NULL which redirects the STDIN_FILENO and STDOUT_FILENO to the only or last file accordingly
 * calls redirect_io_pipe() if there is more than one t_command node which redirects STDIN_FILENO to pipe read_end[0] (last t_command node) and STDOUT_FILENO to pipe write_end (first t_command node) or redirects both FILENOs
 *
 * called in n_builtins_2() after fork() and before execve()
 */
void	redirect_command_io(t_command *c_node)
{
	if (!c_node)
		return ;
	if (c_node->std_in != NULL)
		redirect_io_file(c_node->std_in, 'i', c_node);
	if (c_node->std_out_o != NULL)
		redirect_io_file(c_node->std_out_o, 'o', c_node);
	if (c_node->std_out_a != NULL)
		redirect_io_file(c_node->std_out_a, 'a', c_node);
	if (c_node->size == 1)
		return ;
	redirect_io_pipe(c_node);
}
