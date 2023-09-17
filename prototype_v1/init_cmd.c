/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:48:46 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/17 14:29:20 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_command	*cmd_new(char *cmd)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->flags = NULL;
	node->num_f = 0;
	node->args = NULL;
	node->num_a = 0;
	node->lim = NULL;
	node->std_in = 0;
	node->std_out = 0;
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

/*
 * initialize a linked list where each node is a full command set
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
				*cmds = cmd_new(tmp->token);
			else
				cmd_add_back(cmds, cmd_new(tmp->token));
			i++;
		}
		tmp = tmp->next;
	}
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
