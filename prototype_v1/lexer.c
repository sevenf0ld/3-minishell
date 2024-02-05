/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 23:44:57 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * categorizes enum 0 to 2 and 10 to 11
 * categorizes | > < << >>
 */
void	categorize_symbol(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->token, "|"))
			tmp->symbol = PIPE;
		else if (!ft_strcmp(tmp->token, ">"))
			tmp->symbol = OUT_RE;
		else if (!ft_strcmp(tmp->token, "<"))
			tmp->symbol = IN_RE;
		else if (!ft_strcmp(tmp->token, "<<"))
			tmp->symbol = HD;
		else if (!ft_strcmp(tmp->token, ">>"))
			tmp->symbol = ADD;
		tmp = tmp->next;
	}
}

/*
 * categorizes filename (8) and heredoc's limiter (9)
 * categorize files if any output/input redirection, heredoc's limiter,
	arguments in pipeline
 */
void	categorize_params(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE || tmp->symbol == ADD)
			if (tmp->next != NULL)
				if (tmp->next->symbol != IN_RE && tmp->next->symbol != OUT_RE
					&& tmp->next->symbol != ADD)
					tmp->next->symbol = FILN;
		if (tmp->symbol == HD && tmp->next != NULL)
			tmp->next->symbol = LIM;
		tmp = tmp->next;
	}
}

static void	c_w_a_norme(t_token *t_node)
{
	bool	cmd;
	t_token	*tmp;

	cmd = false;
	tmp = t_node;
	while (tmp != NULL)
	{
		if (tmp->symbol == CMD)
		{
			cmd = true;
			break ;
		}
		if (tmp->symbol == PIPE)
			break ;
		tmp = tmp->prev;
	}
	if (!cmd && t_node->symbol != PIPE && t_node->symbol != IN_RE
		&& t_node->symbol != OUT_RE && t_node->symbol != ADD
		&& t_node->symbol != HD)
		t_node->symbol = CMD;
	else if (cmd)
		t_node->symbol = ARGS;
}

/*
 * categorizes command (5) and arguments (7)

	* categorizes command (executable & builtins)
		and arguments (flags/options included)
 */
void	categorize_cmd_w_args(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (!tmp->prev && tmp->symbol == ANON)
			tmp->symbol = CMD;
		else if (tmp->prev != NULL && tmp->prev->symbol == PIPE)
			tmp->symbol = CMD;
		else if (tmp->prev != NULL && (tmp->prev->symbol == FILN
				|| tmp->prev->symbol == LIM))
			c_w_a_norme(tmp);
		if (tmp->symbol == ANON)
			tmp->symbol = ARGS;
		tmp = tmp->next;
	}
}

/*
 * turns the words into tokens
 * categorizes the tokens
 * group the tokens and set an identifier/separator
 * further break down the tokens for those involving quotes
 * error_handling
 * ╳ expand environment variables (relying on getenv instead of t_fixed)
 * ╳ remove quotes
 * group the command groups
 */
//int lexer(char *pipeline, t_token **tokens, t_status *stat)
int	lexer(char *pipeline, t_mini *mi)
{
	tokenizer(ft_strtrim(pipeline, "    "), &mi->tok, mi->stat);
	double_ll_convert(&mi->tok);
	categorize(&mi->tok);
	split_tokens(&mi->tok);
	if (reject(&mi->tok, mi->stat))
	{
		free_ttkn(&mi->tok);
		free(pipeline);
		return (1);
	}
	expansion(&mi->tok, mi);
	delete_all_element(&mi->tok, "");
	group_cmds(&mi->tok);
	return (0);
}
