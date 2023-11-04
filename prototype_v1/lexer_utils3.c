/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2023/11/04 15:30:21 by maiman-m         ###   ########.fr       */
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


static char	*sub_var(char *to_expand, int len)
{
	int		i;
	int		j;
	char	*extracted;
	char	*sub;
	char	*new;

	i = 0;
	extracted = NULL;
	sub = NULL;
	new = "";
	while (i < len && to_expand[i] != '\0')
	{
		while (i < len && to_expand[i] != '\0' && to_expand[i] != '$')
			i++;
		j = i + 1;
		while (j < len && to_expand[j] != '\0' && to_expand[j] != '$')
			j++;
		extracted = ft_substr(to_expand + i, 0, j - i);
		if (*extracted)
		{
			sub = getenv(extracted + 1);
			if (sub)
				new = join_and_free(new, sub);
		}
		i++;
	}
	if (!*new)
		return (to_expand);
	return (new);
}

static void	expand_env_var(t_token **tokens)
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
	while (tmp != NULL)
	{
		if (tmp->exp)
		{
			og = tmp->token;
			len = ft_strlen(tmp->token);
			while (i < len && tmp->token[i] != '\0' && tmp->token[i] != '$')
				i++;
			sub = sub_var(tmp->token, len);
			if (ft_strcmp(tmp->token, sub))
				tmp->token = join_and_free(ft_substr(tmp->token, 0, i), sub);	
			if (!ft_strcmp(og, tmp->token))
			{
				if (i > 0)
					tmp->token = join_and_free(tmp->token + (len - i), "");
				else
					tmp->token = "";
			}
		}
		tmp = tmp->next;
	}
}

/*
 * set the token boolean exp to true if it is enclosed by double or no quotes
 * calls expand_env_var() which replaces the environment variables and join accordingly
 */
void	expansion(t_token **tokens)
{
	t_token	*tmp;
	
	tmp = *tokens;
	while (tmp != NULL && tmp->symbol != S_Q)
	{
		if (ft_strchr(tmp->token, '$'))
			tmp->exp = true;
		tmp = tmp->next;
	}
	expand_env_var(tokens);
}
