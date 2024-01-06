/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:59 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/06 18:06:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//s 39
//w 34
int	q_l(char *s, char q)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != q)
        {
            fprintf(stderr, "%c", ft_iswhite(s[i]) ? '`' : s[i]);
            i++;
        }
        if (i != 0)
            fprintf(stderr, "\n");
        fprintf(stderr, "%s quote len is %i\n", q == 39 ? "single" : "double", i);
	return (i);
}

static int	w_c(char *s)
{
	int	i;
	int	count;
	int	reset;

	i = 0;
	count = 0;
	reset = 0;
        bool sq = false;
        bool wq = false;
        int sql;
        int wql;
        (void)reset;
	while (s[i] != '\0')
	{
            sql = 0;
            wql = 0;
            if (s[i] == 39)
                sq = true;
            if (s[i] == 34)
                wq = true;
            //fprintf(stderr, "%c %s\n", s[i], !ft_iswhite(s[i]) ? "not" : "ws");
            if (sq)
            {
                sql = q_l(s + i, 39);
                if (sql != 0)
                    sq = false;
            }
            else if (wq)
            {
                wql = q_l(s + i, 34);
                if (wql != 0)
                    wq = false;
            }
            if (sql != 0)
                i += sql + 1;
            else if (wql != 0)
                i += wql + 1;
            else
                i++;

            /*
            if (!ft_iswhite(s[i]) && reset == 0)
            {
                    count += 1;
                    reset = 1;
            }
            else if (ft_iswhite(s[i]))
                    reset = 0;
            i++;
            */
	}
	return (count);
}

//static char	*assign_delim(char *s, char a, t_status *stat)
char	*assign_delim(char *s, char a, t_status *stat)
{
	s = malloc_err(sizeof(char) + 1, stat);
	s[0] = a;
	s[1] = '\0';
	return (s);
}

//static int	w_l(char *s)
int	w_l(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !ft_iswhite(s[i]))
		i++;
	return (i);
}

/*
 * breaks the command and arguments into words based on
 * | > < “ ‘ space
 * 124 62 60 34 39 32
 */
char	**new_split(char *str, t_status *stat)
{
	int		i;
	int		j;
	char	**end;
	//char	*sp_w_q;
        bool            s_q;
        bool            w_q;

	i = -1;
	j = 0;
	//end = init_split_pipeline(str, w_c(str), stat);
        //end = malloc(sizeof(char *) * (w_c(str) + 1));
        end = malloc(sizeof(char *) * (1));
        fprintf(stderr, "wc is %i\n", w_c(str));
	//sp_w_q = NULL;
        s_q = false;
        w_q = false;
        (void)i;
        (void)s_q;
        (void)w_q;
        (void)stat;
        /*
       	while (str[++i] != '\0')
	{
            if (str[i] == 39)
                s_q = true;
            if (str[i] == 34)
                w_q = true;
            if (!ft_iswhite(str[i]))
            {
                    end[j] = ft_strndup(str + i, w_l(str + i));
                    i = i - 1 + w_l(str + i);
                    (void) stat;
                    j += 1;
            }
	}
        */
	end[j] = NULL;
	return (end);
}
