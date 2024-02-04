/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:07:39 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 12:01:44 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*rm_till_end(t_token **tokens)
{
	t_token	*tmp;
	char	*ret;
	char	*trim;

	tmp = *tokens;
	ret = ft_strdup("");
	while (tmp != NULL && tmp->end == false)
	{
		ret = join_and_free(ret, tmp->token);
		ret = join_and_free(ret, " ");
		*tokens = tmp->next;
		// free(tmp);
		tmp = NULL;
		tmp = *tokens;
	}
	if (tmp != NULL && tmp->end == true)
	{
		*tokens = tmp->next;
		// free(tmp);
		tmp = NULL;
	}
	trim = ft_strtrim(ret, " ");
	free(ret);
	return (trim);
}

/*

* init_multi_fa() stores all the OPT and ARGS
	in its respective 2D char array (end marker is NULL)
* init_multi_redir() stores all input, overwrite & append redirections
	in its respectiive int array (end marker is INT_MIN)
 */
void	complete_cmd(t_mini *mi, t_token **tokens, t_command **cmds)
{
	t_command	*c_node;

	c_node = *cmds;
	while (c_node != NULL)
	{
		init_multi_a(tokens, c_node);
		init_multi_l(mi, tokens, c_node);
		init_multi_redir(tokens, c_node);
		c_node->og = rm_till_end(tokens);
		c_node = c_node->next;
	}
}

void	update_cmd_exec(t_command **cmds)
{
	t_command	*c_node;

	c_node = *cmds;
	while (c_node != NULL)
	{
		if (!c_node->cmd)
			c_node->exec = false;
		c_node = c_node->next;
	}
}

void	parser(t_mini *mi)
{
	t_token		**tokens;
	t_command	**cmds;

	tokens = &mi->tok;
	cmds = &mi->cmd;
	cmd_init(tokens, cmds, mi->env, mi->stat);
	double_ll_convert2(cmds);
	mi->limiting = 0;
	complete_cmd(mi, tokens, cmds);
	update_cmd_exec(cmds);
	mi->piping = 0;
	if (*cmds != NULL && (*cmds)->size > 1)
	{
		pipe_init(&mi->pip, (*cmds)->size - 1, mi->stat);
		double_ll_convert3(&mi->pip);
		assign_pipe_ends(*cmds, mi->pip);
		mi->piping = 1;
	}
}
