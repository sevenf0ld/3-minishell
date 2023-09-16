/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:39:09 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/16 16:03:41 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_symbols(t_token *t_node, t_sym to_set)
{
	t_node->symbol = to_set;
	t_node->next->symbol = to_set;
}

void	identify_symbols(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE && tmp->next != NULL)
			if (tmp->next->symbol == IN_RE)
				set_symbols(tmp, HD);
		if (tmp->symbol == OUT_RE && tmp->next != NULL)
			if (tmp->next->symbol == OUT_RE)
				set_symbols(tmp, ADD);
		if (tmp->symbol == PIPE && tmp->next != NULL)
			if (tmp->next->symbol == PIPE)
				set_symbols(tmp, LOR);
		if (tmp->symbol == AMP && tmp->next != NULL)
			if (tmp->next->symbol == AMP)
				set_symbols(tmp, LAND);
		tmp = tmp->next;
	}
}

/*
 * group the tokens into a set of separate commands
 * end=true marks the end of a command
 */
void	group_cmds(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == PIPE && tmp->next != NULL)
			if (tmp->next->symbol != W_Q && tmp->next->symbol != S_Q)
				if (tmp->prev != NULL)
					tmp->prev->end = true;
		if (tmp->symbol == LAND && tmp->next != NULL)
			if (tmp->next->symbol == LAND && tmp->prev != NULL)
				tmp->prev->end = true;
		if (tmp->symbol == LOR && tmp->next != NULL)
			if (tmp->next->symbol == LOR && tmp->prev != NULL)
				tmp->prev->end = true;
		if (tmp->next == NULL)
			tmp->end = true;
		tmp = tmp->next;
	}
}
