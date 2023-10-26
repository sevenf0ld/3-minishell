/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:39:09 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/26 17:59:59 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*join_symbols(t_token *t_node)
{
	t_token	*to_rm;

	t_node->token = ft_strjoin(t_node->token, t_node->next->token);
	to_rm = t_node->next;
	t_node->next = to_rm->next;
	//free(to_rm);
	//to_rm = NULL;
	return (t_node->token);
}

static void	group_symbols(t_token **tokens)
{
	t_token	*tmp;
	t_token	*to_rm;

	tmp = *tokens;
	to_rm = NULL;
	while (tmp != NULL)
	{
		if (tmp->symbol == HD && tmp->next != NULL)
			if (tmp->next->symbol == HD)
				tmp->token = join_symbols(tmp);
		if (tmp->symbol == ADD && tmp->next != NULL)
			if (tmp->next->symbol == ADD)
				tmp->token = join_symbols(tmp);
		tmp = tmp->next;
	}
}

static void	set_symbols(t_token *t_node, t_sym to_set)
{
	t_node->symbol = to_set;
	t_node->next->symbol = to_set;
}

void	identify_symbols(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE && tmp->next != NULL)
			if (tmp->next->symbol == IN_RE)
				set_symbols(tmp, HD);
		if (tmp->symbol == OUT_RE && tmp->next != NULL)
			if (tmp->next->symbol == OUT_RE)
				set_symbols(tmp, ADD);
		tmp = tmp->next;
	}
	group_symbols(tokens);
}

/*
 * group the tokens into a set of separate commands
 * based on pipe since bonus is ditched
 * end=true marks the end of a command
 */
void	group_cmds(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == PIPE && tmp->next != NULL)
			tmp->end = true;
		tmp = tmp->next;
	}
}
