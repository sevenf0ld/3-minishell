/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 16:01:22 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	mini_delim(char a)
{
	if (a == 124 || a == 62 || a == 60 || a == 34 || a == 39 || a == 40 || a == 41 || a == 38)
		return (1);
	return (0);
}

void	categorize_tokens(t_token **tokens, int (f)(char *s, char *t))
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (!f(tmp->token, "|"))
			tmp->symbol = PIPE;
		else if (!f(tmp->token, ">"))
			tmp->symbol = OUT_RE;
		else if (!f(tmp->token, "<"))
			tmp->symbol = IN_RE;
		else if (!f(tmp->token, "\""))
			tmp->symbol = W_Q;
		else if (!f(tmp->token, "'"))
			tmp->symbol = S_Q;
		else if (!f(tmp->token, "("))
			tmp->symbol = OP_BRAC;
		else if (!f(tmp->token, ")"))
			tmp->symbol = CL_BRAC;
		else if (!f(tmp->token, "&"))
			tmp->symbol = AMP;
		tmp = tmp->next;
	}
}

/*
 * turns the words into tokens
 * categorizes the tokens
 */
void	lexer(char *pipeline, t_token **tokens)
{
	char	**words;

	words = new_split(pipeline);
	token_init(words, tokens);
	double_ll_convert(tokens);
	categorize_tokens(tokens, ft_strcmp);
}
