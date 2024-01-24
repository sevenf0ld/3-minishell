/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/24 23:24:31 by maiman-m         ###   ########.fr       */
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

static char    *partial_norme(char *ext, char *s, int start, int i)
{
    char    *sub;
    char    *og;
    char    *rep;
    char    *ret;

    sub = getenv(ext + 1);
    og = s + i;
    /*
    if (og[0] == 39)
        og  += 1;
    */
    while (og[0] == 39)
        og++;
    if (!sub)
        sub = "";
    rep = repl(og, ext, sub, ft_strlen(og));
    ret = ft_substr(s + start, 0, i + 1);
    if (!ret || s[i] == '$' || (s[i] == 34 && s[i + 1] == '$'))
        ret = "";
    ret = ft_strjoin(ret, rep);
    return (ret);
}

static char    *token_partial_repl(char *s, int i, int *close)
{
    char    *ext;
    char    *og;
    int     start;

    og = s + i;
    start = 0;
    if (s[i] == 34)
        i += 1;
    *close = iterate_until_closing(og, s[i]);
    ext = ext_dollar(og);
    return (partial_norme(ext, s, start, i));
}

void	expand_utils(char **token)
{
        t_exp_norme exp_params;
        int         i;

        exp_params = (t_exp_norme){0};
        exp_params.s = *token;
        i = 0;
        while (exp_params.s[i] != '\0')
	{
		decide_word(exp_params.s[i], &exp_params.sq, &exp_params.wq);
                if (!exp_params.sq && exp_params.s[i + 1] != '\0' && exp_params.s[i + 1] != 39)
                {
                    exp_params.part = token_partial_repl(exp_params.s, i, &exp_params.close);
                    *token = exp_params.part;
                    if (!exp_params.part)
                        expand_utils(&exp_params.part);
                    break ;
                }
		i++;
	}
}
