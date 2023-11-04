/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:32:51 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/04 16:13:47 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	handle_in_between(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->pos != 0 && cur->pos != cur->size - 1)
		{
			if (cur->std_in == NULL)
				dup2_err(cur->pipe_fd[0], STDIN_FILENO);
			if (cur->std_out_o == NULL && cur->std_out_a == NULL)
				dup2_err(cur->pipe_fd[1], STDOUT_FILENO);
		}
		cur = cur->next;
	}
}

/*
 * only if there are pipes in the pipeline
 * redirects STDIN_FILENO to pipe read_end[0] for last command group and STDOUT_FILENO to pipe write_end[1] for first command group to pipe ends if there are no file redirection
 * calls handle_in_between() to redirect the command groups STDIN_FILENO and STDOUT_FILENO between the first and last to both pipe ends
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
