/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/16 11:57:49 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	mini_delim(char a)
{
	if (a == 124 || a == 62 || a == 60 || a == 34)
		return (1);
	if (a == 39 || a == 40 || a == 41 || a == 38)
		return (1);
	return (0);
}

void	categorize_token_symbol(t_token **tokens, int (f)(char *s, char *t))
{
	t_token	*tmp;

	tmp = *tokens;
	tmp->symbol = CMD;
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
		else if (tmp->token[0] == '-')
			tmp->symbol = OPT;
		tmp = tmp->next;
	
	}
	categorize_helper(tokens);
}

void	categorize_helper(t_token **tokens)
{
	t_token	*tmp;
	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == PIPE && tmp->next != NULL)
			if (tmp->next->symbol != S_Q && tmp->next->symbol != W_Q)
				tmp->next->symbol = CMD;
		if (tmp->symbol == OUT_RE && tmp->next != NULL)
			if (tmp->next->symbol != OUT_RE)
				tmp->next->symbol = FILN;
		if (tmp->symbol == IN_RE && tmp->next != NULL)
			if (tmp->next->symbol != IN_RE)
				tmp->next->symbol = FILN;
		if (tmp->symbol == FILN && tmp->next != NULL)
			if (tmp->prev != NULL && tmp->prev->symbol == IN_RE)
				tmp->next->symbol = CMD;
		if (tmp->symbol == ANON)
			tmp->symbol = ARGS;
		if (tmp->symbol == PIPE && tmp->prev != NULL)
			if (tmp->prev->symbol == S_Q || tmp->prev->symbol == W_Q)
				if (tmp->next != NULL)
					if (tmp->next->symbol == S_Q || tmp->next->symbol == W_Q)
						tmp->symbol = ARGS;
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
	categorize_token_symbol(tokens, ft_strcmp);
}
