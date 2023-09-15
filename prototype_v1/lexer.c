/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 14:44:57 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * turns the words into tokens
 * categorizes the tokens
 */
void	lexer(char *pipeline, t_token **tokens)
{
	char	delim[] = {124, 62, 60, 34, 39};
	size_t	size;
	char	**words;

	size = sizeof(delim) / sizeof(delim[0]);
	words = new_split(pipeline, delim, size);
	token_init(words, tokens);
	
	t_token *dl;
	dl = double_ll_convert(tokens);
	while (dl != NULL)
	{
		printf("%s\n", dl->token);
		printf("NEXT \x1b[36m%p\x1b[m\n", dl->next);
		dl = dl->prev;
	}

	t_token *sl;
	sl = *tokens;
	while (sl != NULL)
	{
		printf("%s\n", sl->token);
		printf("PREV \x1b[34m%p\x1b[m\n", sl->prev);
		sl = sl->next;
	}
}
