/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:48:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/22 16:59:24 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
   split the symbol(s) concatenated to other characters if q is false
   | > < >> <<
*/
void	split_tokens(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		categorize_symbol(tokens);
		if (tmp->symbol == CMD || tmp->symbol == ARGS || tmp->symbol == FILN
			|| tmp->symbol == LIM)
		{
			if (delim_present(tmp->token))
			{
				separate_delim(tmp->token, tmp, tokens);
				while (tmp->prev != NULL)
					tmp = tmp->prev;
				continue ;
			}
		}
		tmp = tmp->next;
	}
}
