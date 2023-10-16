/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:36:05 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/16 17:32:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	delete_node_attach(t_token **lst, bool value)
{
	t_token	*curr;
	t_token	*to_remove;

	curr = *lst;
	while (curr->next != NULL)
	{
		while (curr->next->rm == value)
		{
			to_remove = curr->next;
			curr->next = curr->next->next;
			if (curr->next == NULL)
			{
				free(to_remove);
				return ;
			}
			free(to_remove);
			to_remove = NULL;
		}
		curr = curr->next;
	}
}

static void	delete_node(t_token **lst, bool value)
{
	t_token	*to_remove;

	if (*lst == NULL)
		return ;
	while ((*lst)->rm == value)
	{
		to_remove = (*lst);
		*lst = (*lst)->next;
		free(to_remove);
		to_remove = NULL;
	}
	delete_node_attach(lst, value);
}

void	manage_quotes(t_token **tokens)
{
	t_token	*tmp;
	int		num;

	tmp = *tokens;
	num = 0;
	while (tmp != NULL) 
	{
		if (!ft_strcmp(tmp->token, "\"") || !ft_strcmp(tmp->token, "'"))
		{
			num += 1;
			if (num == 2)
			{
				if (tmp->next != NULL)
					if (!is_delim(tmp->next->token[0]))
						tmp->next->rm = true;
				num = 0;
			}
		}
		tmp = tmp->next;
	}
	delete_node(tokens, true);
}
