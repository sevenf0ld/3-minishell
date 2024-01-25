/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 00:08:36 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char    *till_dollar(char *s, int i)
{
    char    *ret;
    
    if (i == 0)
        return (NULL);
    ret = ft_strndup(s, i);
    //fprintf(stderr, "up to %s\n", ret);
    return (ret);
}

char    *sub_exp(char *s)
{
    char    *ext;
    char    *sub;
    
    ext = NULL;
    sub = NULL;
    ext = ft_strtrim(ext_dollar(s), "   ");
    sub = getenv(ext + 1);
    if (!sub)
        sub = "";
    //fprintf(stderr, "{%s: %s}\n", ext, sub);
    return (sub);
}

/*
   anything that is not in single quotes and has a dollar sign, expand
*/
char    *expand_utils(char *s)
{
    fprintf(stderr, "%s\n", s);

    int i;
    bool    sq;
    bool    wq;

    i = 0;
    sq = false;
    wq = false;
    while (s[i] != '\0')
    {
        if (s[i] == 39 || s[i] == 34)
            decide_word(s[i], &sq, &wq);
        if (s[i] == '$' && !sq)
        {
            sub_exp(s + i);
            till_dollar(s, i);
            fprintf(stderr, "join %s\n", ft_strjoin(till_dollar(s, i), sub_exp(s + i)));
        }
        i++;
    }

    return (NULL);
}
