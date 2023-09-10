/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:31:36 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 21:27:43 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

t_command	*cmd_new(char *cmd)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->flags = NULL;
	node->input = NULL;
	node->std_in = -1;
	node->std_out = -1;
	node->std_err = -1;
	node->order = -1;
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

void	cmd_init(char **args, t_command **head)
{
	int	i;

	*head = cmd_new(args[0]);
	i = 1;
	while (args[i] != NULL)
		cmd_add_back(head, cmd_new(args[i++]));
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
