/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:18:39 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/03 14:34:06 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static t_token	*get_first_quote(t_token **tokens, t_sym symbol)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == symbol)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_token	*get_last_quote(t_token **tokens, t_sym symbol)
{
	t_token	*tmp;

	tmp = token_last(*tokens);
	while (tmp != NULL)
	{
		if (tmp->symbol == symbol)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

/*
 * get the pair by iterating from front and back of list
 */
void	double_check_quotes(t_token **tokens, t_sym symbol)
{
	t_token	*tmp;
	t_token	*first;
	t_token	*last;
	t_sym	check;

	tmp = *tokens;
	first = get_first_quote(tokens, symbol);
	last = get_last_quote(tokens, symbol);
	check = S_Q;
	if (symbol == S_Q)
		check = W_Q;
	if (!first || !last)
		return ;
	while (tmp != NULL)
	{
		if (tmp == first)
		{
			while (tmp != NULL && tmp != last)
			{
				if (tmp->symbol == check)
					tmp->symbol = ARGS;
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
}
