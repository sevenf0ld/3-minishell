/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:48:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 09:23:46 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	delim_present(char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (s[0] == 39 || s[0] == 34)
		if (s[len - 1] == 39 || s[len - 1] == 34)
			return (0);
	while (s[i] != '\0')
	{
		if (is_delim(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	split_tokens(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		categorize_symbol(tokens);
		if (tmp->symbol == CMD || tmp->symbol == ARGS || tmp->symbol == FILN
			|| tmp->symbol == LIM)
		{
			if (delim_present(tmp->token))
			{
				separate_delim(tmp->token, tmp, tokens);
				while (tmp->prev != NULL)
					tmp = tmp->prev;
				continue ;
			}
		}
		tmp = tmp->next;
	}
}
