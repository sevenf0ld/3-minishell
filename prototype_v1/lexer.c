/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/06 15:24:15 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * categorizes enum 0 to 4
 * categorizes | > < " '
 */
void	categorize_symbol(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	tmp->symbol = CMD;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->token, "|"))
			tmp->symbol = PIPE;
		else if (!ft_strcmp(tmp->token, ">"))
			tmp->symbol = OUT_RE;
		else if (!ft_strcmp(tmp->token, "<"))
			tmp->symbol = IN_RE;
		else if (!ft_strcmp(tmp->token, "\""))
			tmp->symbol = W_Q;
		else if (!ft_strcmp(tmp->token, "'"))
			tmp->symbol = S_Q;
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
                            if (tmp->next->symbol != S_Q && tmp->next->symbol != W_Q)
				tmp->next->symbol = FILN;
		if (tmp->symbol == HD && tmp->next != NULL)
			tmp->next->symbol = LIM;
		tmp = tmp->next;
	}
	categorize_params_norme(tokens);
}

/*
 * categorizes arguments (7) in command set
 * categorize files if any output/input redirection, heredoc's limiter, arguments in pipeline
 */
void	categorize_params_norme(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == ANON)
			tmp->symbol = ARGS;
		if (tmp->symbol == PIPE && tmp->prev != NULL)
			if (tmp->prev->symbol == S_Q || tmp->prev->symbol == W_Q)
				if (tmp->next != NULL)
					if (tmp->next->symbol == S_Q || tmp->next->symbol == W_Q)
						tmp->symbol = ARGS;
		tmp = tmp->next;
	}
}

/*
 * categorizes command (5) and its flags/options (6)
 * categorizes command (executable & builtins) and flags/options
 */
void	categorize_cmdwflags(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == PIPE && tmp->next != NULL)
			if (tmp->next->symbol != S_Q && tmp->next->symbol != W_Q)
				if (tmp->next->symbol != PIPE)
                                    if (tmp->next->symbol != IN_RE && tmp->next->symbol != ADD && tmp->next->symbol != OUT_RE)
                                        tmp->next->symbol = CMD;
		if (tmp->symbol == ARGS && tmp->next != NULL)
			if (tmp->prev != NULL && tmp->prev->prev != NULL)
				if (tmp->prev->symbol == FILN)
					if (tmp->prev->prev->symbol == IN_RE || tmp->prev->prev->symbol == ADD || tmp->prev->prev->symbol == OUT_RE)
						tmp->symbol = CMD;
		if (tmp->token[0] == '-' && tmp->prev != NULL)
			if (ft_strlen(tmp->token) > 1)
				if (tmp->prev->symbol == CMD || tmp->prev->symbol == OPT)
					tmp->symbol = OPT;
		if (tmp->symbol == ARGS && tmp->prev != NULL)
			if (tmp->prev->symbol == FILN)
				tmp->symbol = CMD;
		tmp = tmp->next;
	}
}

void    categorize_quoted(t_token **tokens, t_sym symbol)
{
    t_token *tmp;
    bool    arg;
    t_sym   check;

    tmp = *tokens;
    arg = false;
    check = S_Q;
    if (symbol == check)
        check = W_Q;
    while (tmp != NULL)
    {
        if (tmp->symbol == symbol && !arg)
            arg = true;
        else if (tmp->symbol == symbol && arg)
            arg = false;
        if (tmp->symbol != ARGS && arg && tmp->symbol != symbol && tmp->symbol != check)
            tmp->symbol = ARGS;
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
	char	**words;

	words = new_split(ft_strtrim(pipeline, " 	"), stat);
	token_init(words, tokens, stat);
	double_ll_convert(tokens);
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
