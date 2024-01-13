/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:59 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/13 18:16:50 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//static int	w_c(char *s)
//{
//	int	i;
//	int	count;
//	int	reset;
//
//	i = 0;
//	count = 0;
//	reset = 0;
//	while (s[i] != '\0')
//	{
//		if (is_delim(s[i]))
//			count += 1;
//		else if (!ft_iswhite(s[i]) && reset == 0 && !is_delim(s[i]))
//		{
//			count += 1;
//			reset = 1;
//		}
//		else if (ft_iswhite(s[i]))
//			reset = 0;
//		i++;
//	}
//	return (count);
//}
//
//static char	*assign_delim(char *s, char a, t_status *stat)
//{
//	s = malloc_err(sizeof(char) + 1, stat);
//	s[0] = a;
//	s[1] = '\0';
//	return (s);
//}
//
//static int	w_l(char *s)
//{
//	int	i;
//
//	i = 0;
//	while (s[i] != '\0' && !ft_iswhite(s[i]) && !is_delim(s[i]))
//		i++;
//	return (i);
//}
//
///*
// * breaks the command and arguments into words based on
// * | > < “ ‘ space
// * 124 62 60 34 39 32
// */
//char	**new_split(char *str, t_status *stat)
//{
//	int		i;
//	int		j;
//	char	**end;
//	char	*sp_w_q;
//
//	i = -1;
//	j = 0;
//	end = init_split_pipeline(str, w_c(str), stat);
//	sp_w_q = NULL;
//	while (str[++i] != '\0')
//	{
//		if (!ft_iswhite(str[i]))
//		{
//			if (is_delim(str[i]))
//				end[j] = assign_delim(end[j], str[i], stat);
//			else
//			{
//				end[j] = ft_strndup(str + i, w_l(str + i));
//				i = i - 1 + w_l(str + i);
//			}
//			j += 1;
//		}
//		else
//		{
//			sp_w_q = handle_spaces_btwn_q(str[i - 1], str[i + 1]);
//			if (sp_w_q != NULL)
//				end[j++] = sp_w_q;
//		}
//	}
//	end[j] = NULL;
//	return (end);
//}

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
    if (c == 39 && !*sq)
        *sq = true;
    else if (c == 34 && !*wq)
        *wq = true;
    else if (c == 39 && *sq)
        *sq = false;
    else if (c == 34 && *wq)
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
