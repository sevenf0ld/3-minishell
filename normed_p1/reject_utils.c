/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reject_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:22:18 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/31 11:22:46 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	multi_redir(t_token *t_node, t_status *stat)
{
	t_token	*tmp;

	tmp = t_node;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE || tmp->symbol == ADD
			|| tmp->symbol == HD)
			if (tmp->next != NULL)
				if (tmp->next->symbol == IN_RE || tmp->next->symbol == OUT_RE
					|| tmp->next->symbol == ADD || tmp->next->symbol == HD)
					return (redir_err(tmp->next->token, stat));
		tmp = tmp->next;
	}
	return (0);
}

int	redir_as_end(t_token *t_node, t_status *stat)
{
	t_token	*tmp;

	tmp = t_node;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE || tmp->symbol == ADD
			|| tmp->symbol == HD)
			if (tmp->next == NULL || (tmp->next != NULL
					&& tmp->next->symbol == PIPE))
				return (redir_err(NULL, stat));
		tmp = tmp->next;
	}
	return (0);
}

static int	mult_adj_sym_norme_one(t_token *tmp, int *i, char *s,
		t_status *stat)
{
	if (tmp->symbol == ARGS)
	{
		s = tmp->token;
		if (contain_quotes(s))
			return (0);
		*i = 0;
		while (s[*i] != '\0')
		{
			if (is_delim(s[*i]) && s[*i + 1] != '\0' && is_delim(s[(*i) + 1]))
			{
				if (s[(*i) + 1] == '>')
					return (redir_err(">", stat));
				else
					return (symbols_err(stat));
			}
			(*i)++;
		}
	}
	return (0);
}

int	multi_adjacent_symbols(t_token *t_node, t_status *stat)
{
	int		i;
	char	*s;
	t_token	*tmp;

	i = 0;
	s = NULL;
	tmp = t_node;
	while (tmp != NULL)
	{
		if (mult_adj_sym_norme_one(tmp, &i, s, stat))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
