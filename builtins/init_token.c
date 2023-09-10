/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:09:50 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 21:55:02 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

t_token	*token_new(char *token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = token;
	node->symbol = WORD;
	node->next = NULL;
	return (node);
}

void	token_add_back(t_token **head, t_token *node)
{
	t_token	*old_end;

	if (!node)
		return ;
	old_end = token_last(*head);
	old_end->next = node;
}

void	token_init(char **args, t_token **head)
{
	int	i;

	*head = token_new(args[0]);
	i = 1;
	while (args[i] != NULL)
		token_add_back(head, token_new(args[i++]));
}

t_token	*token_last(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	token_size(t_token *head)
{
	t_token	*tmp;
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
