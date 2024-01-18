/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2024/01/18 21:14:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*join_and_free(char *to_free, char *to_concat)
{
	char	*end;

	end = ft_strjoin(to_free, to_concat);
	//free(to_free);
	//to_free = NULL;
	return (end);
}

char	*sub_var(char *to_expand, int len)
{
    //fprintf(stderr, "to_expand: %s\n", to_expand);
	int		i;
	int		j;
	char	*extracted;
	char	*sub;
	char	*new;
        int     k;

	i = 0;
	extracted = NULL;
	sub = NULL;
	new = "";
        (void) sub;
        (void) new;
        k = i;
	(void) k;
        while (i < len && to_expand[i] != '\0')
	{
		while (i < len && to_expand[i] != '\0' && to_expand[i] != '$')
			i++;
		j = i + 1;
		while (j < len && to_expand[j] != '\0' && (to_expand[j] != '\"' && to_expand[j] != 32 && to_expand[j] != '$'))
			j++;
                extracted = ft_substr(to_expand + i, 0, j - i);
                if (extracted != NULL && *extracted)
                {
                    /*
                    fprintf(stderr, "   extracted [%s]\n", extracted);
                    sub = getenv(extracted + 1);
                    fprintf(stderr, "   getenv [%s]\n", sub);
                    new = ft_substr(to_expand, k, i);
                    fprintf(stderr, "   first index to beginning of extracted [%s]\n", new);
                    new = join_and_free(new, sub);
                    fprintf(stderr, "   joined [%s]\n", new);
                    k = i;
                    fprintf(stderr, "   end of extracted to end of string [%s]\n", ft_substr(to_expand, j, ft_strlen(to_expand) - j));
                    new = join_and_free(new, ft_substr(to_expand, j, ft_strlen(to_expand) - j));
                    fprintf(stderr, "   joined [%s]\n", new);
                    */
                    sub = getenv(extracted + 1);
		    if (sub)
			new = join_and_free(new, sub);
                    fprintf(stderr, "   joined [%s]\n", new);
                }
		i += ft_strlen(extracted);
                //i++;
	}
	return (extracted);
}

static void	expand_env_var(t_token **tokens, t_status *stat)
{
	t_token	*tmp;
	char	*sub;
	int		i;
	int		len;
	char	*og;

	tmp = *tokens;
	sub = NULL;
	i = 0;
	len = 0;
        (void) sub;
        (void) i;
        (void) len;
        (void) og;
        (void) join_and_free;
	while (tmp != NULL)
	{
		if (tmp->exp && ft_strcmp(tmp->token, "$?") != 0)
		{
			og = tmp->token;
			len = ft_strlen(tmp->token);
			while (i < len && tmp->token[i] != '\0' && tmp->token[i] != '$')
				i++;
			sub = sub_var(tmp->token, len);
			//if (ft_strcmp(tmp->token, sub))
			//	tmp->token = join_and_free(ft_substr(tmp->token, 0, i), sub);	
		}
		else if (tmp->exp && !ft_strcmp(tmp->token, "$?"))
                    tmp->token = ft_lltoa(stat->s_code);
		tmp = tmp->next;
	}
}

static void    decide_quote(char c, bool *sq)
{
    if (c == 39 && !*sq)
        *sq = true;
}

int not_in_single(char *s)
{
    int i;
    bool    sq;

    i = 0;
    sq = false;
    while (s[i] != '\0')
    {
        if (s[i] == 39)
            decide_quote(s[i], &sq);
        i++;
    }
    if (!sq)
        return (1);
    return (0);
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
                if (not_in_single(tmp->token))
		    tmp->exp = true;
	    tmp = tmp->next;
	}
        (void) stat;
        (void) expand_env_var;
        expand_env_var(tokens, stat);
}
