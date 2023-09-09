/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:09:50 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 00:55:32 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_list	*sl_new(t_list *head, char *token)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->cmd = token;
	node->next = NULL;
	head = node;
	return (head);
}

void	sl_add_back(t_list **head, char *token)
{
	t_list	*node;
	t_list	*old_end;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node->cmd = token;
	node->next = NULL;
	old_end = sl_last(*head);
	old_end->next = node;
}

t_list	*sl_initialize(char **args, t_list *head)
{
	int	i;

	head = sl_new(head, args[0]);
	i = 1;
	while (args[i] != NULL)
		sl_add_back(&head, args[i++]);
	return (head);
}

t_list	*sl_last(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	sl_size(t_list *head)
{
	t_list	*tmp;
	int		counter;

	tmp = head;
	counter = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		counter++;
	}
	return (counter);
}
