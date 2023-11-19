/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:09:11 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/19 23:48:51 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void print_inode(int fd, char *name) {
 struct stat info;
 if (fstat(fd, &info) != 0)
   fprintf(stderr,"fstat() error for %s %d: %s\n",name,fd,strerror(errno));
 else
   fprintf(stderr, "╳ The inode of %s is %d\n", name, (int) info.st_ino);
}

/*
void	assign_pipe_ends(t_command *c_node)
{
	t_command	*cur;
	int			i;
	int			loop;
	int			ends[c_node->size * 2];

	cur = c_node;
	i = cur->size;
	loop = 0;
	while (i > 0)
	{
		pipe_err(ends + loop);
		loop += 2;
		i--;
	}
	for (size_t j = 0; j < sizeof(ends)/sizeof(ends[0]); j++)
	while (cur != NULL)
	{
		if (cur->pos == 0)
		{
			cur->write_end = ends[1];
		}
		else if (cur->pos == cur->size - 1)
		{
			cur->read_end = ends[2];
		}
		else
		{
			cur->read_end = ends[0];
			cur->write_end = ends[3];
		}
		cur = cur->next;
	}
}
*/

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
	return end;
}

/*
 * [0] | [1] | [2] | [3] | [4] | [5]
 *     0     1     2     3     4
 * if even and odd (in between):
 * 		write to the same index
 * 		read from index - 1
 *
 * if first:
 * 		write to the same index
 * 		read from file or SI
 * 			file redir is already handled so stdin is either pointing to SI or file
 *
 * if last:
 * 		write to file or SO
 * 		read from index - 1
 * 			file redir is already handled so stdout is either pointing to SO or file
 */
void	assign_pipe_ends(t_command *c_node, t_pipe *p_node)
{
	t_command	*cur;
	t_pipe		*end;

	cur = c_node;
	end = NULL;
	while (cur != NULL)
	{
		/*
		end = retrieve_pipe(p_node, cur->pos);
		cur->read_end = end->prev->pipe_fd[0];
		cur->write_end = end->pipe_fd[1];
		*/
		/*
		end = retrieve_pipe(p_node, cur->pos - 1);
		cur->read_end = end->pipe_fd[0];
		cur->write_end = end->next->pipe_fd[1];
		*/
		if (cur->pos > 0 && cur->pos < cur->size - 1)
		{
			end = retrieve_pipe(p_node, cur->pos);
			if (end)
			{
				cur->read_end = end->prev->pipe_fd[0];
				cur->write_end = end->pipe_fd[1];
				fprintf(stderr, "FOR THE COMMAND %s\n", cur->cmd);
				print_inode(cur->read_end, "<-> assign in between, R");
				print_inode(cur->write_end, "<-> assign in between, W");
			}
		}
		if (cur->pos == 0)
		{
			end = retrieve_pipe(p_node, cur->pos);
			if (end)
			{
				cur->read_end = STDIN_FILENO;;
				cur->write_end = end->pipe_fd[1];
				fprintf(stderr, "FOR THE COMMAND %s\n", cur->cmd);
				print_inode(cur->read_end, "0 assign first, R");
				print_inode(cur->write_end, "0 assign first, W");
			}
		}
		if (cur->pos == cur->size - 1)
		{
			//end = retrieve_pipe(p_node, cur->pos);
			end = retrieve_pipe(p_node, cur->pos - 1);
			//if (end && end->prev)
			if (end)
			{
				//cur->read_end = end->prev->pipe_fd[0];
				cur->read_end = end->pipe_fd[0];
				cur->write_end = STDOUT_FILENO;
				fprintf(stderr, "FOR THE COMMAND %s\n", cur->cmd);
				print_inode(cur->read_end, "N assign last, R");
				print_inode(cur->write_end, "N assign last, W");
			}
		}
		cur = cur->next;
	}
}
