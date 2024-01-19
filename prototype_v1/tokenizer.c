/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:59 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 15:39:58 by maiman-m         ###   ########.fr       */
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

static int iterate_until_closing(char *s, char c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            return i;
        }
        i++;
    }
    return i;
}

static void    decide_quote(char c, bool *sq, bool *wq)
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

void    new_split(char *str, t_token **tokens, t_status *stat)
{
    bool sq = false;
    bool wq = false;
    int i = 0;
    int close = 0;
    int check;
    int start = -1;
    int count = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39 || str[i] == 34)
        {
            decide_quote(str[i], &sq, &wq);
            if (sq || wq)
                close = iterate_until_closing(str, str[i]);
        }
        if (str[i] != 32 || (str[i] == 32 && (sq || wq)))
        {
            close += 1;
            if (start == -1)
                start = i;
        }
        else if (str[i] == 32 && (!wq && !sq))
        {
            // skip the spaces outside of quotes
            if (check != close)
            {
                check = close;
                continue ;
            }
            token_init(ft_substr(str, start, (size_t) i - start), tokens, stat, count);
            count += 1;
            start = -1;
        }
        i++;
    }
    token_init(ft_substr(str, start, (size_t) i - start), tokens, stat, count);
}
