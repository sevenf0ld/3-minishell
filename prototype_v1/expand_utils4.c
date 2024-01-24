/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/25 02:08:14 by maiman-m         ###   ########.fr       */
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

static char    *partial_norme(char *ext, char *s, int start, int i, int *shift)
{
    char    *sub;
    char    *og;
    char    *rep;
    char    *ret;

    sub = getenv(ext + 1);
    og = s + i;
    while (og[0] == 39)
        og++;
    if (!sub)
        sub = "";
    rep = repl(og, ext, sub, ft_strlen(og));
    *shift = ft_strlen(sub) - ft_strlen(ext) + ft_strlen(og);
    fprintf(stderr, "SHIFT %i\n", *shift);
    int end = i;
    if (end != 0)
        end += 1;
    ret = ft_substr(s + start, 0, end);
    if (!ret || s[i] == '$' || (s[i] == 34 && s[i + 1] == '$'))
        ret = "";
    ret = ft_strjoin(ret, rep);
    return (ret);
}

static char    *token_partial_repl(char *s, int i, int *close, int *shift)
{
    char    *ext;
    char    *og;
    int     start;

    og = s + i;
    start = 0;
    *close = iterate_until_closing(og, s[i]);
    ext = ext_dollar(og);
    return (partial_norme(ft_strtrim(ext, "     "), s, start, i, shift));
}

void	expand_utils(char **token, int shift)
{
        t_exp_norme exp_params;
        int         i;

        exp_params = (t_exp_norme){0};
        exp_params.s = *token;
        i = shift;
        while (exp_params.s[i] != '\0')
	{
		decide_word(exp_params.s[i], &exp_params.sq, &exp_params.wq);
                if (!exp_params.sq && exp_params.s[i + 1] != '\0' && exp_params.s[i + 1] != 39)
                {
                    exp_params.part = token_partial_repl(exp_params.s, i, &exp_params.close, &shift);
                    fprintf(stderr, "PARAM S %s\n", exp_params.s);
                    fprintf(stderr, "PARAM S + i %s\n", exp_params.s + i);
                    fprintf(stderr, "PARAM S + close %s\n", exp_params.s + exp_params.close);
                    *token = exp_params.part;
                    fprintf(stderr, "PARAM S + shift %s (%i)\n", exp_params.part + shift, shift);
                    //expand_utils(&exp_params.part, shift);
                    return ;
                }
		i++;
	}
}
