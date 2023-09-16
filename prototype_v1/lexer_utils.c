/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:39:09 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/16 13:58:41 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
		if (tmp->next == NULL)
			tmp->end = true;
		tmp = tmp->next;
	}
}
