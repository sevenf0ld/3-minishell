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

void	set_multi(t_split *split_cmd, t_command **c_node)
{
	t_split		*tmp;
	int			i;
	int			j;
	
	tmp = split_cmd;
	i = 0;
	j = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == OPT)
			i += 1;
		if (tmp->symbol == MSG)
			j += 1;
		tmp = tmp->next;
	}
	if (i != 0)
		(*c_node)->num_f = i;
	if (j != 0)
		(*c_node)->num_i = j;
}

//does not handle multi flags and multi inputs which needs to malloced
void	set_cmd(char **full_cmd, t_command **c_node)
{
	t_split		*split_cmd;
	t_split		*tmp;
	t_command	*node;

	split_cmd = NULL;
	split_init(full_cmd, &split_cmd);
	set_split_type(&split_cmd, ft_strcmp);
	set_multi(split_cmd, c_node); 
	
	t_split	*sym;
	for (sym = split_cmd; sym != NULL; sym = sym->next)
		printf("~~~ %s ~~~ %i\n", sym->each, sym->symbol);

	tmp = split_cmd;
	node = *c_node;
	while (tmp != NULL)
	{
		if (tmp->symbol == CMD)
			node->cmd = tmp->each;
		else if (tmp->symbol == OPT)
			node->flags = tmp->each;
		else if (tmp->symbol == MSG)
			node->input = tmp->each;
		tmp = tmp->next;
	}
	printf("NUM CHECK (f)%i (i)%i\n", node->num_f, node->num_i);
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
