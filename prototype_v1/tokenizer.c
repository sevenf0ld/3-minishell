/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:59 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/22 18:01:07 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	tokenizer_norme_init(t_token_norme *token_params, char *s)
{
	token_params->s = s;
	token_params->sq = false;
	token_params->wq = false;
	token_params->i = 0;
	token_params->close = 0;
	token_params->check = 0;
	token_params->start = -1;
	token_params->count = 0;
	token_params->sub = NULL;
}


static void	decide_quote(char c, bool *sq, bool *wq)
{
	if (c == 39 && !*sq && !*wq)
		*sq = true;
	else if (c == 34 && !*wq && !*sq)
		*wq = true;
	else if (c == 39 && *sq && !*wq)
		*sq = false;
	else if (c == 34 && *wq && !*sq)
		*wq = false;
}

static int	iterate_until_closing(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	within_alongside_quotes(t_token_norme *token_params, char *s, char mode)
{
	if (mode == 'w')
	{
		decide_quote(s[token_params->i], &token_params->sq, &token_params->wq);
		if (token_params->sq || token_params->wq)
			token_params->close = iterate_until_closing(s, s[token_params->i]);
	}
	else if (mode == 'a')
	{
		token_params->close += 1;
		if (token_params->start == -1)
			token_params->start = token_params->i;
	}
}

void    tokenizer(char *s, t_token **tokens, t_status *stat)
{
        t_token_norme	token_params;

	token_params = (t_token_norme){0};
	token_params.tokens = tokens;
	token_params.stat = stat;
	tokenizer_norme_init(&token_params, s);
	while (s[token_params.i] != '\0')
	{
		if (decide_chunk(&token_params, s))
			continue ;
		(token_params.i)++;
	}
	token_init(ft_substr(s, token_params.start,
			(size_t)(token_params.i) - (token_params.start)),
		tokens, stat, token_params.count);
	free(s);
}
