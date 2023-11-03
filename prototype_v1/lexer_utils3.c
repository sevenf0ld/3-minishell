/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2023/11/03 17:20:56 by maiman-m         ###   ########.fr       */
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
 * issues:
 * when the token i$HOMEi is split on space
 * 		_____
 *     /	 \
 *	   i	HOMEi
 * i seems to be an environment variable when it actually is not
 * joins to the token's original content
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

char	*sub_var(char *to_expand, int len)
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

/*
 * issues:
 * does not replace the token's original content ✔
 * replaces the environment variable but does not join to the rest ✔
 */
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
*/

void	expansion(t_token **tokens)
{
	t_token	*tmp;
	t_token	*first;
	t_token	*last;

	tmp = *tokens;
	first = get_first_quote(tokens, W_Q);
	last = get_last_quote(tokens, W_Q);
	if (!first || !last)
		return ;
	while (tmp != NULL)
	{
		if (tmp == first)
		{
			while (tmp != NULL && tmp != last)
			{
				if (ft_strchr(tmp->token, '$'))
					tmp->exp = true;
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	expand_env_var(tokens);
}
