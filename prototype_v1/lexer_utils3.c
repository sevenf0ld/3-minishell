/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2023/10/31 18:05:48 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*join_and_free(char *to_free, char *to_concat)
{
	char	*end;

	end = ft_strjoin(to_free, to_concat);
	//free(to_free);
	//to_free = NULL;
	return (end);
}

/*
static void	expand_env_var(t_token **tokens)
{
	t_token	*tmp;
	char	**dollar;
	char	*sub;
	int		i;
	char	*og;

	tmp = *tokens;
	dollar = NULL;
	sub = NULL;	
	og = NULL;
	while (tmp != NULL)
	{
		if (tmp->exp)
		{
			i = 0;
			og = tmp->token;
			dollar = ft_split(tmp->token, '$');
			while (dollar[i] != NULL)
			{
				printf("CHECK DOLLAR %s\n", dollar[i]);
				sub = getenv(dollar[i]);
				if (sub && i == 0)
					tmp->token = sub;
				else if (sub && i > 0)
					tmp->token = join_and_free(tmp->token, sub);
				i++;				
			}
			if (!ft_strcmp(og, tmp->token))
				tmp->token = "";
		}
		tmp = tmp->next;
	}
}
*/

void sub_var(char **s)
{
	char	*t;
	int		i;
	int		j;
	int		len;
	char	*extracted;
	char	*sub;
	char	*new;

	t = *s;
	i = 0;
	len = ft_strlen(t);
	extracted = NULL;
	new = "";
	while (i < len && t[i] != '\0')
	{
		while (i < len && t[i] != '\0' && t[i] != '$')
			i++;
		j = i + 1;
		while (j < len && t[j] != '\0' && t[j] != '$')
			j++;
		extracted = ft_substr(t + i, 0, j - i);
		if (*extracted)
		{
			printf("sub_var (extracted) -> %s\n", extracted);
			sub = getenv(extracted + 1);
			printf("SUB %s\n", sub);
			if (sub)
				new = join_and_free(new, sub);
			printf("NEW %s\n", new);
		}
		i++;
	}
}

static void	expand_env_var(t_token **tokens)
{
	t_token	*tmp;
	char	**dollar;
	char	*sub;
	int		i;
	char	*og;

	tmp = *tokens;
	dollar = NULL;
	sub = NULL;	
	i = 0;
	og = NULL;
	while (tmp != NULL)
	{
		if (tmp->exp)
		{
			dollar = ft_split(tmp->token, ' ');
			while (dollar[i] != NULL)
			{
				sub_var(&dollar[i]);
				//printf("expand_env_var -> %s\n", dollar[i]);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void	expansion(t_token **lst)
{
	t_token	*curr;
	int		check[2];

	if (*lst == NULL)
		return ;
	curr = *lst;
	curr = curr->next;
	while (curr != NULL)
	{
		check[0] = 0;
		check[1] = 0;
		if (!ft_strcmp(curr->prev->token, "\'"))
			check[0] = 1;
		if (ft_strchr(curr->token, '$'))
			check[1] = 1;
		if (check[0] == 0 && check[1] == 1)
			curr->exp = true;
		curr = curr->next;
	}
	expand_env_var(lst);
}
