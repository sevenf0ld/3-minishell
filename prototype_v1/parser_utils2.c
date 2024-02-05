/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:09:11 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 09:59:43 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static t_pipe	*retrieve_pipe(t_pipe *p_node, int n)
{
	t_pipe	*end;

	end = p_node;
	while (end != NULL)
	{
		if (end->pos == n)
			break ;
		end = end->next;
	}
	return (end);
}

static void	assign_norme(t_command *c_node, t_pipe *end, t_pipe *p_node, int i)
{
	if (i == 0)
	{
		end = retrieve_pipe(p_node, c_node->pos);
		if (end)
		{
			c_node->read_end = STDIN_FILENO;
			c_node->write_end = end->pipe_fd[1];
		}
	}
	else if (i == 1)
	{
		end = retrieve_pipe(p_node, c_node->pos - 1);
		if (end)
		{
			c_node->read_end = end->pipe_fd[0];
			c_node->write_end = STDOUT_FILENO;
		}
	}
}

/*
 * retrieve_pipe() returns the corresponding t_pipe for t_command
 * [0] | [1] | [2] | [3] | [4] | [5]
 *     0     1     2     3     4
 * if even and odd (in between/in general):
 * 		write to the same index
 * 		read from index - 1
 *
 * if first:
 * 		write to the same index
 * 		read from file or SI
 *
 * if last:
 * 		write to file or SO
 * 		read from index - 1
 */
void	assign_pipe_ends(t_command *c_node, t_pipe *p_node)
{
	t_command	*cur;
	t_pipe		*end;

	cur = c_node;
	end = NULL;
	while (cur != NULL)
	{
		if (cur->pos == 0)
			assign_norme(cur, end, p_node, 0);
		if (cur->pos == cur->size - 1)
			assign_norme(cur, end, p_node, 1);
		if (cur->pos > 0 && cur->pos < cur->size - 1)
		{
			end = retrieve_pipe(p_node, cur->pos);
			if (end)
			{
				cur->read_end = end->prev->pipe_fd[0];
				cur->write_end = end->pipe_fd[1];
			}
		}
		cur = cur->next;
	}
}
