/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:07:39 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/19 23:04:19 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
/*
void print_inode(int fd, char *name) {
 struct stat info;
 if (fstat(fd, &info) != 0)
   fprintf(stderr,"fstat() error for %s %d: %s\n",name,fd,strerror(errno));
 else
   fprintf(stderr, "╳ The inode of %s is %d\n", name, (int) info.st_ino);
}
*/
static void	set_multi_fa(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;
	int		i;
	int		j;

	tmp = *tokens;
	i = 0;
	j = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == OPT && c_node->flags != NULL)
			c_node->flags[i++] = ft_strdup(tmp->token);
		if (tmp->symbol == ARGS && c_node->args != NULL)
			c_node->args[j++] = ft_strdup(tmp->token);
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
}

void	init_multi_fa(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == OPT)
			c_node->num_f += 1;
		if (tmp->symbol == ARGS)
			c_node->num_a += 1;
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_f > 0)
		c_node->flags = malloc_err(sizeof(char *) * (c_node->num_f + 1));
	if (c_node->num_a > 0)
		c_node->args = malloc_err(sizeof(char *) * (c_node->num_a + 1));
	set_multi_fa(tokens, c_node);
}

static void	rm_till_end(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL && tmp->end == false)
	{
		*tokens = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = *tokens;
	}
	if (tmp != NULL && tmp->end == true)
	{
		*tokens = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}

/*
 * calls init_multi_fa() which stores all the flags (OPT) and arguments (ARGS) in its respective 2D char array (end marker is NULL)
 * calls init_multi_redir() which stores all the input and output (overwrite & append) redirections in its respect int array (end marker is INT_MIN)
 */
void	complete_cmd(t_token **tokens, t_command **cmds)
{
	t_token		*tmp;
	t_command	*c_node;

	tmp = *tokens;
	c_node = *cmds;
	while (c_node != NULL)
	{
		init_multi_fa(tokens, c_node);
		init_multi_redir(tokens, c_node);
		rm_till_end(tokens);
		c_node = c_node->next;
	}	
}

void	parser(t_token **tokens, t_command **cmds, int ro, int ri)
{
	t_pipe	*pipes;

	pipes = NULL;
	cmd_init(tokens, cmds);
	double_ll_convert2(cmds);
	complete_cmd(tokens, cmds);
	pipe_init(&pipes, (*cmds)->size - 1);
	double_ll_convert3(&pipes);
	assign_pipe_ends(*cmds, pipes);
	ro = -1;
	ri = -1;
	/*
	int i = 0;
	for (t_command *cur = *cmds; cur != NULL; cur = cur->next)
	{
		fprintf(stderr, "in parser (%i)-> %s\n", i, cur->cmd);
		redirect_command_io(cur);
		//print_inode(ro, "in parser, restore stdout");
		//print_inode(ri, "in parser, restore stdin");
		if (cur->size > 1)
		{
			print_inode(cur->write_end, "in parser, ONE write end");
			print_inode(cur->read_end, "in parser, ONE read end");
			if (cur->write_end != -1 && cur->write_end != ro)
				dup2_err(cur->write_end, ro);
			print_inode(cur->write_end, "in parser, TWO write end");
			print_inode(cur->read_end, "in parser, TWO read end");
			ri = -1;
		}
		i++;
	}
	*/
}
