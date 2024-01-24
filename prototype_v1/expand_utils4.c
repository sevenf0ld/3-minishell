/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/24 22:37:37 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	decide_word(char c, bool *sq, bool *wq)
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

static char    *ext_dollar(char *s)
{
    int i;
    int j;
    
    i = 0;
    if (s[i] == 39)
        i += 1;
    while (s[i] != '\0')
    {
        if (s[i] == '$')
            break ;
        i++;
    }
    j = i + 1;
    while (s[j] != '\0')
    {
        if (s[j] == 39 || s[j] == 34 || s[j] == '$')
            break ;
        j++;
    }
    return (ft_substr(s, i, j - i));
}

char    *token_partial_repl(char *s, int i, int *close)
{
    char    *ext;
    char    *rep;
    char    *ret;
    char    *og;
    int     start;

    rep = NULL;
    og = s + i;
    start = 0;
    if (s[i] == 34)
        i += 1;
    *close = iterate_until_closing(og, s[i]);
    ext = ext_dollar(og);
    if (og[0] == 39)
        og  += 1;
    rep = repl(og, ext, getenv(ext + 1), ft_strlen(og));
    ret = ft_substr(s + start, 0, i + 1);
    if (!ret || s[i] == '$' || (s[i] == 34 && s[i + 1] == '$'))
        ret = "";
    ret = ft_strjoin(ret, rep);
    return (ret);
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
