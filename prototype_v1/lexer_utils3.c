/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2024/01/20 06:55:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
   og           refers to the original string passed in
   displace     refers to the word to be replaced
   sub          refers to the word to replace displace with
*/
static char    *repl(char *og, char *displace, char *sub, int len_og)
{
    // get the length of each param
    //int len_og = strlen(og);
    int len_dis = strlen(displace);
    int len_sub = strlen(sub);

    int occur = -1;
    // shift is initialized to the original string and it will be shifted to the right
    char *shift = og;
    // extracted will be wherever displace is found in shift/og
    char *extracted = strstr(shift, displace);
    while (extracted != NULL)
    {
        occur++;
        extracted = strstr(shift, displace);
        if (extracted != NULL)
            // shift is shifted to the right till the end of extracted
            shift = extracted + len_dis;
    }
    //printf("displace occurs %i amount of times in og\n", occur);

    int diff = len_sub - len_dis;
    //printf("difference in characters between sub and displace\n%s - %s = %i\n", sub, displace, len_sub - len_dis);
    // "hello helloworld" (16)
    // "goodbye goodbyeworld" (20)
    // "goodbye" - "hello / 7 - 5 (2)
    // 2 occurrences * 2 (4)
    // 16 + 4 = 20
    char *ret = malloc(sizeof(char) * (len_og + (diff * occur) + 1));
    char *tmp = ret;
    int moved;

    while (occur-- && occur >= 0)
    {
        shift = strstr(og, displace);
        
        // gives a segfault because strlen is unsafe
        //moved = len_og - strlen(shift);
        // get the length of beginning of og till the first occurence of displace
        moved = shift - og;
        
        //ret = strncpy(ret, og, moved);
        // if strncpy into ret, ret will have to increment which loses the part before displace
        //tmp = strncpy(tmp, og, moved);
        // copy the part from beginning of og till the first occurence of displace
        strncpy(tmp, og, moved);
        
        //shift tmp to the end which is also right before the beginning of displace
        tmp += moved;
        
        //tmp = strcpy(tmp, sub);
        // copy sub into tmp which is also right at where displace begins
        strcpy(tmp, sub);
        
        //shift tmp to the end of sub
        tmp += len_sub;
        
        //shift og to after the substitued displace
        og += moved + len_dis;
    }
    strcpy(tmp, og);
    return (ret);
}

static char    *sub_exp(char *s, int len, char **key, char **val)
{
    int i;
    char    *ret;

    i = 0;
    ret = NULL;
    while (key[i] != NULL)
    {
        ret = repl(s, key[i], val[i], len);
        if (ret != NULL)
        {
            s = ret;
            len = ft_strlen(s);
        }
        i++;
    }
    return (ret);
}

static char    **init_expandables(char *to_expand, int len, t_status *stat)
{
	int	i;
	int	j;
	char	*displace;
        int     count;
        char    **exp;

	i = 0;
	displace = NULL;
        count = 0;
        exp = NULL;
        (void) count;
        (void) exp;
        while (i < len && to_expand[i] != '\0')
	{
		while (i < len && to_expand[i] != '\0' && to_expand[i] != '$') 
			i++;
		j = i + 1;
		while (j < len && to_expand[j] != '\0' && (to_expand[j] != '\"' && to_expand[j] != 32 && to_expand[j] != '$'))
			j++;
                displace = ft_substr(to_expand + i, 0, j - i);
                if (displace && *displace)
                    count += 1;
                i += ft_strlen(displace);
	}
        exp = malloc_err(sizeof(char *) * (count + 1), stat);
        exp[count] = NULL;
        return (exp);
}

static char    **get_exp_key(char *to_expand, int len, t_status *stat)
{
	int	i;
	int	j;
	char	*displace;
        int     k;
        char    **exp;
        int     len_dis;

	i = 0;
	displace = NULL;
        k = 0;
        exp = init_expandables(to_expand, len, stat);
        while (i < len && to_expand[i] != '\0')
	{
		while (i < len && to_expand[i] != '\0' && to_expand[i] != '$') 
			i++;
		j = i + 1;
		while (j < len && to_expand[j] != '\0' && (to_expand[j] != '\"' && to_expand[j] != 32 && to_expand[j] != '$'))
			j++;
                displace = ft_substr(to_expand + i, 0, j - i);
                len_dis = ft_strlen(displace);
                if (displace && *displace)
                {
                    if (displace[len_dis - 1] == 39)
                        displace = ft_strndup(displace, len_dis - 1);
                    exp[k++] = displace;
                }
                i += len_dis;
	}
        return (exp);
}

static char    **get_exp_value(char *to_expand, int len, t_status *stat, char **key)
{
	int	i;
    char    *sub;
    char    **exp;

	i = 0;
        sub = NULL;
        exp = init_expandables(to_expand, len, stat);
        while (key[i] != NULL)
	{
            sub = getenv(key[i] + 1);   
            if (sub != NULL)
                exp[i] = sub;
            else
                exp[i] = "";
            i++;
	}
        return (exp);
}

static void expand_env_var(t_token **tokens, t_status *stat)
{
	t_token	*tmp;
        int     len;
        char    **exp_key;
        char    **exp_value;

	tmp = *tokens;
        exp_key = NULL;
        exp_value = NULL;
        (void) exp_key;
        (void) exp_value;
	while (tmp != NULL)
	{
            if (tmp->exp && ft_strcmp(tmp->token, "$?") != 0)
            {
                len = ft_strlen(tmp->token);
                exp_key = get_exp_key(tmp->token, len, stat);
                exp_value = get_exp_value(tmp->token, len, stat, exp_key);
                tmp->token = sub_exp(tmp->token, len, exp_key, exp_value);
            }
            else if (tmp->exp && !ft_strcmp(tmp->token, "$?"))
                tmp->token = ft_lltoa(stat->s_code);
            tmp = tmp->next;
	}
}

static void    decide_quote(char c, bool *sq, bool *wq)
{
    if (c == 39 && !*sq && !*wq)
        *sq = true;
    else if (c == 34 && !*wq && !*sq)
        *wq = true;
    //else if (c == 39 && *sq && !*wq)
    //    *sq = false;
    //else if (c == 34 && *wq && !*sq)
    //    *wq = false;
}

static int  not_in_single(char *s)
{
    int i;
    bool    sq;
    bool    wq;

    i = 0;
    sq = false;
    wq = false;
    while (s[i] != '\0')
    {
        if (s[i] == 39 || s[i] == 34)
            decide_quote(s[i], &sq, &wq);
        i++;
    }
    if ((!sq && wq) || (sq && wq))
        return (1);
    return (0);
}

static int  not_standalone_dollar(char *s)
{
    if (!ft_strcmp(s, "$") || !ft_strcmp(s, "\"$\""))
        return (0);
    return (1);
}

/*
 * set the token boolean exp to true if it is enclosed by double or no quotes
 * calls expand_env_var() which replaces the environment variables and join accordingly
 */
void	expansion(t_token **tokens, t_status *stat)
{
	t_token	*tmp;
	
	tmp = *tokens;
	while (tmp != NULL)
	{
            if (ft_strchr(tmp->token, '$'))
                if (not_in_single(tmp->token) || not_standalone_dollar(tmp->token))
		    tmp->exp = true;
	    tmp = tmp->next;
	}
    expand_env_var(tokens, stat);
}
