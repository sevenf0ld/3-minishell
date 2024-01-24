/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/25 00:50:21 by maiman-m         ###   ########.fr       */
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

static char    **init_expandables(char *to_expand, int len)
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
        exp = malloc(sizeof(char *) * (count + 1));
        exp[count] = NULL;
        return (exp);
}

static char    **get_exp_key(char *to_expand, int len)
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
        exp = init_expandables(to_expand, len);
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

static char    **get_exp_value(char *to_expand, int len, char **key)
{
	int	i;
        char    *sub;
        char    **exp;

	i = 0;
        sub = NULL;
        exp = init_expandables(to_expand, len);
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

/*
char	*sub_exp(char *s, int len, char *key, char *val)
{
	char	*ret;

	ret = NULL;
        ret = repl(s, key, val, len);
        if (ret != NULL)
            len = ft_strlen(s);
	return (ret);
}
*/

char	*sub_exp(char *s, int len, char **key, char **val)
{
	int		i;
	char	*ret;

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

static char    *partial_norme(char *ext, char *s, int start, int i)
{
    fprintf(stderr, "   EXT |%s|\n", ft_strtrim(ext, "   "));
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
    ret = ft_substr(s + start, 0, i + 1);
    if (!ret || s[i] == '$' || (s[i] == 34 && s[i + 1] == '$'))
        ret = "";
    ret = ft_strjoin(ret, rep);
    
    int len = ft_strlen(ext);
    char **exp_key = get_exp_key(ext, len);
    char **exp_value = get_exp_value(ext, len, exp_key);
    for (int i = 0; exp_key[i] != NULL; i++)
        fprintf(stderr, "{%s: %s}\n", exp_key[i], exp_value[i]);
    //s = sub_exp(s, ft_strlen(s), ext, sub);
    s = sub_exp(s, ft_strlen(s), exp_key, exp_value);


    //return (ret);
    (void) ext;
    (void) s;
    (void) start;
    (void) i;
    (void) len;
    (void) exp_key;
    (void) exp_value;
    return (s);
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
