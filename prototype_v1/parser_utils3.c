/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:32:51 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/29 13:28:46 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * if no file redirect to pipe
 * 		if in between
 * 			stdin -> read_end[0]
 * 			stdout -> write_end[1]
 *
 * need to add error handling for dup2
 */
static void	handle_in_between(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->pos != 0 && cur->pos != cur->size - 1)
		{
				dup2(cur->pipe_fd[0], STDIN_FILENO);
				dup2(cur->pipe_fd[1], STDOUT_FILENO);
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
 *
 * need to add error handling for dup2
 * need to close unused ends
 * need to add error handling for close
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
				close(cur->pipe_fd[0]);
				//dup2(cur->pipe_fd[1], STDOUT_FILENO);
				dup2(open("fake_stdout.txt", O_APPEND), STDOUT_FILENO);
				//printf("hi im the first %s\n", cur->cmd);
			}
		}
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
		{
			if (cur->pos == cur->size - 1)
			{
				close(cur->pipe_fd[1]);
				//dup2(cur->pipe_fd[0], STDIN_FILENO);
				dup2(open("fake_stdin.txt", O_RDONLY), STDIN_FILENO);
				//printf("hello im last %s\n", cur->cmd);
			}
		}
		cur = cur->next;
	}
	handle_in_between(c_node);
}
