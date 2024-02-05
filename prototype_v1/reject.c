/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:37:27 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 09:24:57 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	pipe_first_last(t_token *t_node, t_status *stat)
{
	t_token	*tmp;
	t_token	*last;

	tmp = t_node;
	last = token_last(t_node);
	if (tmp->symbol == PIPE || last->symbol == PIPE)
		return (pipe_related_err(stat));
	return (0);
}

int	multi_pipe(t_token *t_node, t_status *stat)
{
	t_token	*tmp;

	tmp = t_node;
	while (tmp != NULL)
	{
		if (tmp->symbol == PIPE)
		{
			if (tmp->next != NULL && tmp->next->symbol == PIPE)
				return (pipe_related_err(stat));
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
   ╰ pipe as the first or last node
   ╰ unterminated quotes
        ╰ single quote
        ╰ double quote
   ╰ nothing after redirection symbol / redirection as the last node
   ╰ multiple adjacent symbols
        ╰ in one node
        ╰ across multiple nodes (redirections and pipe)
*/
int	reject(t_token **tokens, t_status *stat)
{
	if (pipe_first_last(*tokens, stat))
		return (1);
	if (unterminated_quotes(*tokens, stat))
		return (1);
	if (redir_as_end(*tokens, stat))
		return (1);
	if (multi_adjacent_symbols(*tokens, stat))
		return (1);
	if (multi_redir(*tokens, stat))
		return (1);
	if (multi_pipe(*tokens, stat))
		return (1);
	return (0);
}
