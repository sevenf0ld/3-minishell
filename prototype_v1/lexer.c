/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/13 19:04:45 by maiman-m         ###   ########.fr       */
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

/*
 * categorizes command (5)
 * categorizes command (executable & builtins) and flags/options
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
                    if (tmp->prev->symbol == PIPE || tmp->prev->symbol == FILN)
                        tmp->symbol = CMD;
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
 */
void	lexer(char *pipeline, t_token **tokens, t_status *stat)
{
        new_split(ft_strtrim(pipeline, "     "), tokens, stat);
        double_ll_convert(tokens);
	categorize_symbol(tokens);
        categorize_params(tokens);
        categorize_cmd_w_args(tokens);

        //char	**words;

	//words = new_split(ft_strtrim(pipeline, " 	"), stat);
	//token_init(words, tokens, stat);
	//double_ll_convert(tokens);
	//categorize_symbol(tokens);
        // BONUS
        //turns S_Q to ARGS
	//double_check_quotes(tokens, W_Q);
	//double_check_quotes(tokens, S_Q);
	
        //reject_unterminated_q(tokens, W_Q, stat);
	//reject_unterminated_q(tokens, S_Q, stat);
	//expansion(tokens, stat);
	//manage_quotes(tokens);
	//identify_symbols(tokens);
	//categorize_params(tokens);
	//categorize_cmdwflags(tokens);
        //categorize_quoted(tokens, W_Q);
        //categorize_quoted(tokens, S_Q);
        //group_cmds(tokens);
	//delete_quotes_after_expand(tokens, W_Q);
	//delete_quotes_after_expand(tokens, S_Q);
}
