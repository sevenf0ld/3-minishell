/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 16:15:51 by maiman-m         ###   ########.fr       */
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
 * categorize files if any output/input redirection, heredoc's limiter, arguments in pipeline
 */
void	categorize_params(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE || tmp->symbol == ADD)
			if (tmp->next != NULL)
		                if (tmp->next->symbol != IN_RE && tmp->next->symbol != OUT_RE && tmp->next->symbol != ADD)
			            tmp->next->symbol = FILN;
		if (tmp->symbol == HD && tmp->next != NULL)
			tmp->next->symbol = LIM;
		tmp = tmp->next;
	}
}

void    categorize_cmd_args_norme(t_token *token)
{
    t_token *tmp;
    bool    cmd;

    tmp = token;
    cmd = false;
    while (tmp != NULL)
    {
        if (tmp->symbol == PIPE)
            break ;
        if (tmp->symbol == CMD)
            cmd = true;
        tmp = tmp->prev;
    }
    if (!cmd)
        token->symbol = CMD;
    else
        token->symbol = ARGS;
}

/*
 * categorizes command (5) and arguments (7)
 * categorizes command (executable & builtins) and arguments (flags/options included)
 */
void	categorize_cmd_w_args(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
            if (tmp->symbol == ANON)
            {
                if (tmp->prev == NULL)
                    tmp->symbol = CMD;
                else if (tmp->prev != NULL)
                {
                    if (tmp->prev->symbol == PIPE || tmp->prev->symbol == LIM)
                        tmp->symbol = CMD;
                    else if (tmp->prev->symbol == FILN || tmp->prev->symbol == LIM)
                        categorize_cmd_args_norme(tmp);
                    else
                        tmp->symbol = ARGS;
                }
            }
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
int lexer(char *pipeline, t_token **tokens, t_status *stat)
{
        new_split(ft_strtrim(pipeline, "    "), tokens, stat);
        double_ll_convert(tokens);
        categorize_symbol(tokens);
        categorize_params(tokens);
        categorize_cmd_w_args(tokens);
        split_tokens(tokens, stat);
        if (reject(tokens, stat))
            return (1);
	expansion(tokens, stat);
        group_cmds(tokens);
        return (0);
}
