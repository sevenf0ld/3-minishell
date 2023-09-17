/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:07:39 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/17 13:25:19 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * t_token nodes which have been initialized into t_command nodes will be removed
 */
void	rm_till_end(t_token **tokens)
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
 *
 */
void	set_multi_fa(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;
	int		i;
	int		j;

	tmp = *tokens;
	i = 0;
	j = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == OPT)
			c_node->flags[i++] = ft_strdup(tmp->token);
		if (tmp->symbol == ARGS)
			c_node->args[j++] = ft_strdup(tmp->token);
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
}

/*
 * malloc enough space for each (t_command) command set's flags and arguments
 */
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
			break;
		tmp = tmp->next;
	}
	printf("DETECTED: f (%i) and a (%i)\n", c_node->num_f, c_node->num_a);
	if (c_node->num_f > 0)
		c_node->flags = malloc(sizeof(char *) * (c_node->num_f + 1));
	if (c_node->num_a > 0)
		c_node->args = malloc(sizeof(char *) * (c_node->num_a + 1));
	//set_multi_fa(tokens, c_node);
}

/*
 *
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
		rm_till_end(tokens);
		c_node = c_node->next;
	}	
}

/*
 * create a linked list where each node is a full command set
 */
void	init_cmd(t_token **tokens, t_command **cmds)
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
				*cmds = cmd_new(tmp->token);
			else
				cmd_add_back(cmds, cmd_new(tmp->token));
			i++;
		}
		tmp = tmp->next;
	}
}

/*
 *
 */
void	parser(t_token **tokens, t_command **cmds)
{
	init_cmd(tokens, cmds);
	complete_cmd(tokens, cmds);
}
