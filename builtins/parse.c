/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:01:08 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 18:32:59 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

/*
 * iterate over each token (node)
 * if it is a pipe, that is an indication of a new command (node) for the next token
 * all the token nodes before the pipe token node is a singular command node
 *
 * iterate over each command (node)
 * iterate over each token (node)
 * continously update the token
 * only update the command if the token is a pipe
 */
void	parser(t_command **cmds, int size, int (f)(char *s, char *t), t_token *tokens)
{
	int			i;
	t_command	*cur_cmd;
	t_token		*cur_tok;

	i = 0;
	cur_cmd = *cmds;
	cur_tok = tokens;
	while (cur_tok != NULL)
	{
		if (!f(cur_tok->token, "|"))

		cur_tok = cur_tok->next;
	}
}
