/*
 * ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:01:08 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/11 12:45:32 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	set_cmd(char **full_cmd, t_command **c_node)
{
	t_command	*ptr;
	t_split		*split_cmd;

	split_cmd = NULL;
	split_init(full_cmd, &split_cmd);
	set_split_type(&split_cmd, ft_strcmp);
	
	t_split	*sym;
	for (sym = split_cmd; sym != NULL; sym = sym->next)
		printf("~~~ %s ~~~ %i\n", sym->each, sym->symbol);

	ptr = *c_node;
}

/*
 * split on pipe instead of on space
 * each token:
 * 		cmd + flags + input + redir
 * a linked list split which splits the token into nodes to set the type
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
