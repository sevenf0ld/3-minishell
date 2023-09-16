/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:07:39 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/16 21:34:00 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * create a linked list where each node is a full command set
 */
void	parser(t_token **tokens, t_command **cmds)
{
	t_token		*tmp;
	int			i;

	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == CMD)
		{
			if (i == 0)
				*cmds = cmd_new(tmp->token);
			else
				cmd_add_back(cmds, cmd_new(tmp->token));
			i++;
		}
		tmp = tmp->next;
	}
}
