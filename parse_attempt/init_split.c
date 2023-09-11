/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:28:40 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/11 16:20:30 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

t_split	*split_new(char *split)
{
	t_split	*node;

	node = malloc(sizeof(t_split));
	if (!node)
		return (NULL);
	node->each = split;
	node->symbol = -1;
	node->next = NULL;
	return (node);
}

void	split_add_back(t_split **head, t_split *node)
{
	t_split	*old_end;

	if (!node)
		return ;
	old_end = split_last(*head);
	old_end->next = node;
}

void	split_init(char **args, t_split **head)
{
	int	i;

	*head = split_new(args[0]);
	i = 1;
	while (args[i] != NULL)
		split_add_back(head, split_new(args[i++]));
}

t_split	*split_last(t_split *head)
{
	t_split	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	split_size(t_split *head)
{
	t_split	*tmp;
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
