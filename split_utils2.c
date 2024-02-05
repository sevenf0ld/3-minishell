/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:48:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 19:02:40 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	slot_in_token(t_token *t_node, char *s, t_token **tokens, char *r)
{
	t_token	*new;

	new = NULL;
	new = token_new(s, t_node->stat);
	new->next = t_node;
	if (t_node->prev == NULL)
	{
		t_node->prev = new;
		*tokens = new;
	}
	else
	{
		new->prev = t_node->prev;
		t_node->prev->next = new;
		t_node->prev = new;
	}
	t_node->token = r;
	categorize(tokens);
}

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

static void	sep_delim_dual(char *s, t_token *t_node, t_token **tokens, int i)
{
	if (i > 0)
		slot_in_token(t_node, ft_substr(s, 0, i), tokens,
			ft_substr(s, i, (int)ft_strlen(s)));
	else
		slot_in_token(t_node, ft_substr(s, 0, 2), tokens,
			ft_substr(s, 2, (int)ft_strlen(s)));
	free(s);
}

static void	sep_delim_single(char *s, t_token *t_node, t_token **tokens, int i)
{
	if (i > 0)
		slot_in_token(t_node, ft_substr(s, 0, i), tokens,
			ft_substr(s, i, (int)ft_strlen(s)));
	else
		slot_in_token(t_node, ft_substr(s, 0, 1), tokens,
			ft_substr(s, 1, (int)ft_strlen(s)));
	free(s);
}

void	separate_delim(char *s, t_token *t_node, t_token **tokens)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (s[i] != '\0')
	{
		if (is_hd(s, i, len) || is_add(s, i, len))
			return (sep_delim_dual(s, t_node, tokens, i));
		else if (is_pipe(s[i]) || is_in_re(s[i]) || is_out_re(s[i]))
			return (sep_delim_single(s, t_node, tokens, i));
		i++;
	}
}
