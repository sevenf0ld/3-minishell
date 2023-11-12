/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:32:51 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/12 10:40:38 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static void print_inode(int fd, char *name) {
 struct stat info;
 if (fstat(fd, &info) != 0)
   fprintf(stderr,"fstat() error for %s %d: %s\n",name,fd,strerror(errno));
 else
   fprintf(stderr, "╳ The inode of %s is %d\n", name, (int) info.st_ino);
}

static void	handle_in_between(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->pos > 0 && cur->pos < cur->size - 1)
		{
			if (cur->std_in == NULL)
			{
				fprintf(stderr, "in btwn %s redirect stdin to read end\n", cur->cmd);
				print_inode(STDIN_FILENO, "before pointing to pipe read");
				dup2_err(cur->pipe_fd[0], STDIN_FILENO);
				print_inode(STDIN_FILENO, "after pointing to pipe read");
			}
			if (cur->std_out_o == NULL && cur->std_out_a == NULL)
			{
				fprintf(stderr, "in btwn %s redirect stdout to write end\n", cur->cmd);
				print_inode(STDOUT_FILENO, "before pointing to pipe write");
				dup2_err(cur->pipe_fd[1], STDOUT_FILENO);
				print_inode(STDOUT_FILENO, "after pointing to pipe write");
			}
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
		if (cur->pos == 0)
		{
			if (cur->std_out_o == NULL && cur->std_out_a == NULL)
			{
				close_err(cur->pipe_fd[0]);
				fprintf(stderr, "%s redirect stdout to write end\n", cur->cmd);
				print_inode(STDOUT_FILENO, "first command stdout before pointing to write end");
				//fprintf(stderr, "pid is %d\n", getpid());
				dup2_err(cur->pipe_fd[1], STDOUT_FILENO);
				print_inode(STDOUT_FILENO, "first command stdout after pointing to write end");
				//fprintf(stderr, "pid is %d\n", getpid());
			}
		}
		if (cur->pos == cur->size - 1)
		{
			if (cur->std_in == NULL)
			{
				close_err(cur->pipe_fd[1]);
				fprintf(stderr, "%s redirect stdin to read end\n", cur->cmd);
				print_inode(STDIN_FILENO, "last command stdin before pointing to read end");
				//fprintf(stderr, "pid is %d\n", getpid());
				dup2_err(cur->pipe_fd[0], STDIN_FILENO);
				print_inode(STDIN_FILENO, "last command stdin after pointing to read end");
				//fprintf(stderr, "pid is %d\n", getpid());
			}
		}
		cur = cur->next;
	}
	/*
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
	}
	*/
	handle_in_between(c_node);
}
