/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:32:29 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/16 18:03:34 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_bonus_symbols(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == OP_BRAC && tmp->next != NULL)
			if (tmp->next->symbol != IN_RE)
				tmp->next->symbol = CMD;
		if (tmp->symbol == LAND && tmp->next != NULL)
			if (tmp->next->symbol != LAND && tmp->next->symbol != OP_BRAC)
				if (tmp->next->symbol != PIPE)
					tmp->next->symbol = CMD;
		if (tmp->symbol == LOR && tmp->next != NULL)
			if (tmp->next->symbol != LOR && tmp->next->symbol != OP_BRAC)
				if (tmp->next->symbol != PIPE)
					tmp->next->symbol = CMD;
		tmp = tmp->next;
	}

}
