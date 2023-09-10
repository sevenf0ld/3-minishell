/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:31:36 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 18:33:03 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	command_init(t_token *tokens, t_command **cmds, int (f)(char *s, char *t))
{
	t_token	*tmp;
	int		total;
	int		i;

	tmp = tokens;
	total = 0;
	i = -1;
	while (tmp != NULL)
	{
		if (!f(tmp->token, "|"))
			total += 1;
		tmp = tmp->next;
	}

	printf("no. of commands: %i\n", total + 1);

	cmds = malloc(sizeof(t_command) * (total + 1));
	while (++i < total + 1)
	{
		cmds[i].cmd = NULL;
		cmds[i].flags = NULL;
		cmds[i].input = NULL;
		cmds[i].std_in = -1;
		cmds[i].std_out = -1;
		cmds[i].std_err = -1;
		cmds[i].order = i + 1;
		cmds[i].next = NULL;
	}
	parser(cmds, total + 1, f, tokens);
}
