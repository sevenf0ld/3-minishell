/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/25 14:17:49 by maiman-m         ###   ########.fr       */
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
    while (og[0] == 39)
        og++;
    if (!sub)
        sub = "";
    rep = repl(og, ext, sub, ft_strlen(og));
    int end = i;
    if (end != 0)
        end += 1;
    ret = ft_substr(s + start, 0, end);
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
    *close = iterate_until_closing(og, s[i]);
    ext = ext_dollar(og);
    return (partial_norme(ft_strtrim(ext, "     "), s, start, i));
}

char    *utils(char *partial, char *og, int call)
{
    fprintf(stderr, "UTILS: partial (%s) and og (%s)\n", partial, og);
    if (call == 0)
        og = partial;
    if (!ft_strcmp(og, partial))
        return (NULL);
    og = repl(og, partial, getenv(partial + 1), ft_strlen(og));
    fprintf(stderr, "OG: %s\n", og);
    return og;
}

void	expand_utils(char **token, int call)
{
    (void) call;
        t_exp_norme exp_params;
        int i;
        char    *s;

        exp_params = (t_exp_norme){0};
        exp_params.s = *token;
        s = NULL;
        i = 0;
        while (exp_params.s[i] != '\0')
	{
		decide_word(exp_params.s[i], &exp_params.sq, &exp_params.wq);
                if (!exp_params.sq && exp_params.s[i + 1] != '\0' && exp_params.s[i + 1] != 39)
                {
                    exp_params.part = token_partial_repl(exp_params.s, i, &exp_params.close);
                    utils(exp_params.part, *token, call);
                    if (call == 0)
                        *token = exp_params.part;
                    call += 1;
                    fprintf(stderr, "\x1b[43m PARAM part as is %s \x1b[m\n", exp_params.part);
                    s = ext_dollar(exp_params.part);
                    if (s != NULL && ft_strlen(s) != 0)
                    {
                        *token = exp_params.part;
                        fprintf(stderr, "\x1b[44m DOLLAR %s \x1b[m\n", s);
                        exp_params.part = utils(s, *token, call);
                        *token = exp_params.part;
                    }
                    fprintf(stderr, "\x1b[43m PARAM part as is %s \x1b[m\n", exp_params.part);
                    s = ext_dollar(exp_params.part);
                    if (s != NULL && ft_strlen(s) != 0)
                    {
                        *token = exp_params.part;
                        fprintf(stderr, "\x1b[44m DOLLAR %s \x1b[m\n", s);
                        exp_params.part = utils(s, *token, call);
                        *token = exp_params.part;
                    }
                    fprintf(stderr, "\x1b[43m PARAM part as is %s \x1b[m\n", exp_params.part);
                    s = ext_dollar(exp_params.part);
                    if (s != NULL && ft_strlen(s) != 0)
                    {
                        *token = exp_params.part;
                        fprintf(stderr, "\x1b[44m DOLLAR %s \x1b[m\n", s);
                        exp_params.part = utils(s, *token, call);
                        *token = exp_params.part;
                    }
                    return ;
                }
		i++;
	}
}
