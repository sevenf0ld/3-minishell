/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:01:08 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 22:56:14 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	set_cmd(char **full_cmd, t_command **c_node)
{
	t_command	*ptr;

	ptr = *c_node;
	ptr->cmd = full_cmd[0];
	if (full_cmd[1] == NULL)
		return ;
	if (full_cmd[1][0] == '-')
		ptr->flags = full_cmd[1];
	else
		ptr->input = full_cmd[1];
}

/*
 * split on pipe instead of on space
 * each token:
 * 		cmd + flags + input + redir
 */
void	parser(t_token **tokens, t_command **cmds)
{
	t_token		*tmp;
	char		**full_cmd;
	t_command	*cur;

	tmp = *tokens;
	cur = *cmds;
	while (tmp != NULL)
	{
		full_cmd = ft_split(tmp->token, ' ');
		set_cmd(full_cmd, &cur);
		//free full_cmd
		cur = cur->next;
		tmp = tmp->next;
	}
}
