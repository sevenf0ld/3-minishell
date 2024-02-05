/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:30:26 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/22 18:01:41 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * | > <
 */
int	is_delim(char a)
{
	if (a == 124 || a == 62 || a == 60)
		return (1);
	return (0);
}

static void	tokenize_word(t_token_norme *token_params, char *s)
{
	token_params->sub = ft_substr(s, token_params->start,
			(size_t)token_params->i - token_params->start);
	if (!all_whitespace(token_params->sub))
		token_init(token_params->sub, token_params->tokens,
			token_params->stat, token_params->count);
	else
		check_free_and_null(&token_params->sub);
	token_params->count += 1;
	token_params->start = -1;
}

int	decide_chunk(t_token_norme *token_params, char *s)
{
	if (s[token_params->i] == 39 || s[token_params->i] == 34)
		within_alongside_quotes(token_params, s, 'w');
	if (s[token_params->i] != 32 || (s[token_params->i] == 32
			&& (token_params->sq || token_params->wq)))
		within_alongside_quotes(token_params, s, 'a');
	else if (s[token_params->i] == 32
		&& (!token_params->wq && !token_params->sq))
	{
		if (token_params->check != token_params->close)
		{
			token_params->check = token_params->close;
			return (1);
		}
		tokenize_word(token_params, s);
	}
	return (0);
}
