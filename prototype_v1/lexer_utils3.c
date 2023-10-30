/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2023/10/30 16:26:02 by maiman-m         ###   ########.fr       */
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

int	look_for_dollar(char *to_search)
{
	int	i;

	if (!to_search)
		return (0);
	i = 0;
	while (to_search[i] != '\0')
	{
		if (to_search[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_dollar(char *store)
{
	unsigned int	i;
	char			*aluminium;

	i = 0;
	if (!*store)
		return (NULL);
	while (store[i] != '\0' && store[i] != '$')
		i++;
	aluminium = ft_substr(store, 0, i + 1);
	return (aluminium);
}

char	*update_store(char *store)
{
	unsigned int	i;
	char			*new;
	size_t			len;

	if (!look_for_dollar(store))
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	i = 0;
	while (store[i] != '\0' && store[i] != '$')
		i++;
	len = ft_strlen(store);
	new = ft_substr(store, i + 1, len);
	free(store);
	store = NULL;
	return (new);
}

static void	expand_env_var(t_token **tokens)
{
	t_token	*tmp;
	char	**dollar;
	char	*sub;
	//int		i;
	char	*og;

	tmp = *tokens;
	dollar = NULL;
	sub = NULL;	
	og = NULL;
	while (tmp != NULL)
	{
		if (tmp->exp)
		{
			/*
			dollar = ft_strchr(tmp->token, '$') + 1;
			sub = getenv(dollar);
			if (sub)
				tmp->token = sub;
			else
				tmp->token = " ";
			*/
			/*
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
			*/
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
