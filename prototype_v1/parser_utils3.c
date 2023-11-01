/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:32:51 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/01 18:38:56 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * if no file redirect to pipe
 * 		if in between
 * 			stdin -> read_end[0]
 * 			stdout -> write_end[1]
 */
static void	handle_in_between(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->pos != 0 && cur->pos != cur->size - 1)
		{
				dup2_err(cur->pipe_fd[0], STDIN_FILENO);
				dup2_err(cur->pipe_fd[1], STDOUT_FILENO);
		}
		cur = cur->next;
	}
}

/*
 * if no file redirect to pipe
 * 		if first command
 * 			redirect to write_end[1] (write to) instead of stdout
 * 		if last command
 * 			redirect to read_end[0] (read from) instead of stdin
 * 		if in between
 */
void	handle_pipe_ends(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->std_in == NULL)
		{
			if (cur->pos == 0)
			{
				close_err(cur->pipe_fd[0]);
				dup2_err(cur->pipe_fd[1], STDOUT_FILENO);
			}
		}
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
		{
			if (cur->pos == cur->size - 1)
			{
				close_err(cur->pipe_fd[1]);
				dup2_err(cur->pipe_fd[0], STDIN_FILENO);
			}
		}
		cur = cur->next;
	}
	handle_in_between(c_node);
}
