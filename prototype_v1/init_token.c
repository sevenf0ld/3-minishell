/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:09:50 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/28 11:03:20 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * symbol will be set to -1 after testing
 */
t_token	*token_new(char *token, t_status *stat)
{
	t_token	*node;

	node = malloc_err(sizeof(t_token));
	node->token = token;
	node->symbol = ANON;
	node->end = false;
	node->rm = false;
	node->exp = false;
	node->enclosed = false;
        node->stat = stat;
	node->prev = NULL;
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

/*
 * converts the splitted pipeline into individual tokens
 */
void	token_init(char **args, t_token **head, t_status *stat)
{
	int	i;

	*head = token_new(args[0], stat);
	i = 1;
	while (args[i] != NULL)
		token_add_back(head, token_new(args[i++], stat));
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
