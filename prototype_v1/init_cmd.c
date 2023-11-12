/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:48:46 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/11 13:32:03 by maiman-m         ###   ########.fr       */
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

t_command	*cmd_new(char *cmd, int n)
{
	t_command	*node;

	node = malloc_err(sizeof(t_command));
	node->pos = n;
	node->size = 0;
	node->cmd = cmd;
	node->flags = NULL;
	node->num_f = 0;
	node->args = NULL;
	node->num_a = 0;
	node->lim = NULL;
	node->std_in = NULL;
	node->num_si = 0;
	node->std_out_o = NULL;
	node->num_so_o = 0;
	node->std_out_a = NULL;
	node->num_so_a = 0;
	pipe_err(node->pipe_fd);
	fprintf(stderr, "CHECKING PIPE ENDS FOR %s, %i (read) and %i (write)\n", node->cmd, node->pipe_fd[0], node->pipe_fd[1]);
	print_inode(node->pipe_fd[0], "pipe read end");
	print_inode(node->pipe_fd[1], "pipe write end");
	node->next = NULL;
	return (node);
}

void	cmd_add_back(t_command **head, t_command *node)
{
	t_command	*old_end;

	if (!node)
		return ;
	old_end = cmd_last(*head);
	old_end->next = node;
}

static void	set_cmd_size(t_command *head)
{
	int			n;
	t_command	*tmp;

	n = cmd_size(head);
	tmp = head;
	while (tmp != NULL)
	{
		tmp->size = n;
		tmp = tmp->next;
	}
}

/*
 * converts the categorized and grouped tokens into individual command sets/groups
 */
void	cmd_init(t_token **tokens, t_command **cmds)
{
	t_token		*tmp;
	int			i;

	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == CMD)
		{
			if (i == 0)
				*cmds = cmd_new(tmp->token, i);
			else
				cmd_add_back(cmds, cmd_new(tmp->token, i));
			i++;
		}
		tmp = tmp->next;
	}
	set_cmd_size(*cmds);
}

t_command	*cmd_last(t_command *head)
{
	t_command	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	cmd_size(t_command *head)
{
	t_command	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
