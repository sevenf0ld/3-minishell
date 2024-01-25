/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/25 23:29:05 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

/*
   anything that is not in single quotes and has a dollar sign, expand
*/
char    *expand_utils(char *s)
{
    (void) iterate_until_closing;
    fprintf(stderr, "%s\n", s);

    int i;
    bool    sq;
    bool    wq;
    int close;
    bool    c;

    i = 0;
    sq = false;
    wq = false;
    close = 0;
    (void) close;
    while (s[i] != '\0')
    {
        c = sq;
        if (s[i] == 39 || s[i] == 34)
        {
            decide_word(s[i], &sq, &wq);
            if (c && !sq)
            {
                //fprintf(stderr, "%c %s\n", s[i], c ? "true" : "false");
                i += 1;
                continue ;
            }
        }
        if (s[i] == '$' && !sq)
            fprintf(stderr, "ext dollar: %s\n", ext_dollar(s + i));
        //fprintf(stderr, "%c %s\n", s[i], sq ? "true" : "false");
        i++;
    }

    return (NULL);
}
