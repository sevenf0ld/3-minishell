/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/24 16:57:09 by maiman-m         ###   ########.fr       */
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
    rep = NULL;
    int     start;

    // i to shift start of s and + 1 to skip the quote
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

//echo '$USER'$HOME"$PATH"
//echo '$HOME'"$PATH"'$HOME'
void	expand_utils(char **token, t_status *stat)
{
	int		i = 0;
	bool	sq = false;
	bool	wq = false;
        int     close = 0;
        char    *part;
        char    *s = *token;
        (void) stat;
	
        while (s[i] != '\0')
	{
		decide_word(s[i], &sq, &wq);
                if (!sq)
                {
                    part = token_partial_repl(s, i, &close);
                    *token = part;
                    if (part != NULL)
                        fprintf(stderr, "repl: %s\n", part);
                    if (!part)
                        expand_utils(&part, stat);
                    break ;
                }
		i++;
	}
}
