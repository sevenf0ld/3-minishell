/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:43:53 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/19 23:53:03 by maiman-m         ###   ########.fr       */
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
   fprintf(stderr, "┈ The inode of %s is %d\n", name, (int) info.st_ino);
}

t_pipe	*pipe_new(int n)
{
	t_pipe	*node;

	node = malloc_err(sizeof(t_pipe));
	node->pos = n;
	pipe_err(node->pipe_fd);
	fprintf(stderr, "----------------------%i---------------------\n", n);
	print_inode(node->pipe_fd[0], "pipe_new r ->");
	print_inode(node->pipe_fd[1], "pipe_new w ->");
	fprintf(stderr, "----------------------%i---------------------\n", n);
	node->next = NULL;
	return (node);
}

t_pipe	*pipe_last(t_pipe *head)
{
	t_pipe	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	pipe_add_back(t_pipe **head, t_pipe *node)
{
	t_pipe	*old_end;
	if (!node)
		return ;
	old_end = pipe_last(*head);
	old_end->next = node;
}

void	pipe_init(t_pipe **pipes, int loop)
{
	t_pipe	*tmp;
	int		i;

	tmp = *pipes;
	i = 0;
	while (i < loop)
	{
		if (i == 0)
			*pipes = pipe_new(i);
		else
			pipe_add_back(pipes, pipe_new(i));
		i++;
	}
}
