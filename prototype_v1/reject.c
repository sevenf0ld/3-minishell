/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:37:27 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/15 15:58:09 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void    multi_redir(t_token *t_node, t_status *stat)
{
    t_token *tmp;

    tmp = t_node;
    while (tmp != NULL)
    {
        if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE || tmp->symbol == ADD || tmp->symbol == HD)
            if (tmp->next != NULL)
                if (tmp->next->symbol == IN_RE || tmp->next->symbol == OUT_RE || tmp->next->symbol == ADD || tmp->next->symbol == HD)
                {
                    redir_err(tmp->next->token, stat);
                    return ;
                }
        tmp = tmp->next;
    }
    
}

void    redir_as_end(t_token *t_node, t_status *stat)
{
    t_token *tmp;

    tmp = t_node;
    while (tmp != NULL)
    {
        if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE || tmp->symbol == ADD || tmp->symbol == HD)
            if (tmp->next == NULL || (tmp->next != NULL && tmp->next->symbol == PIPE))
            {
                redir_err(NULL, stat);
                return ;
            }
        tmp = tmp->next;
    }
}

void    multi_adjacent_symbols(t_token *t_node, t_status *stat)
{
    t_token *tmp;
    char    *s;
    int     i;

    tmp = t_node;
    s = NULL;
    i = 0;
    while (tmp != NULL)
    {
        if (tmp->symbol == ARGS)
        {
            s = tmp->token;
            i = 0;
            while (s[i] != '\0')
            {
                if (is_delim(s[i]) && s[i + 1] != '\0' && is_delim(s[i + 1]))
                {
                    symbols_err(stat);
                    return ;
                }
                i++;
            }
        }
        tmp = tmp->next;
    }
}

void    unterminated_quotes(t_token *t_node, t_status *stat)
{
    t_token *tmp;
    char    *s;
    int     i;
    bool    sq;
    bool    wq;

    tmp = t_node;
    s = NULL;
    i = 0;
    sq = false;
    wq = false;
    while (tmp != NULL)
    {
        if (tmp->symbol == ARGS)
        {
            s = tmp->token;
            i = 0;
            sq = false;
            wq = false;
            while (s[i] != '\0')
            {
                if (s[i] == 39 && !sq && !wq)
                    sq = true;
                else if (s[i] == 39 && sq && !wq)
                    sq = false;
                else if (s[i] == 34 && !wq && !sq)
                    wq = true;
                else if (s[i] == 34 && wq && !sq)
                    wq = false;
                i++;
            }
            if (sq && !wq)
                quote_err("\'", stat);
            else if (wq && !sq)
                quote_err("\"", stat);
        }
        tmp = tmp->next;
    }
}

/*
void    pipe_first_last(t_token *t_node, t_status *stat)
{
    if (t_node->symbol == PIPE)
        first_err(stat);
    if (token_last(t_node)->symbol == PIPE)
        first_err(stat);
}
*/

void    pipe_first_last(char *s, t_status *stat)
{
    size_t  len;

    len = ft_strlen(s);
    if (s[0] == 124 || s[len - 1] == 124)
        first_err(stat);
}

void    multi_pipe(t_token *t_node, t_status *stat)
{
    t_token *tmp;

    tmp = t_node;
    while (tmp != NULL)
    {
        if (tmp->symbol == PIPE)
        {
            if (tmp->next != NULL && tmp->next->symbol == PIPE)
            {
                first_err(stat);
                return ;
            }
        }
        tmp = tmp->next;
    }
}

/*
   ╰ pipe as the first node (character) in the command group
   ╰ nothing after pipe / pipe as the last node (character)
   ╰ unterminated quotes
        ╰ single quote
        ╰ double quote
   ╰ nothing/pipe after redirection symbol / redirection as the last node
   ╰ multiple adjacent symbols
        ╰ in one node (ARGS only)
        ╰ across multiple nodes (redirections and pipe)
*/
void    reject(char *s, t_token **tokens, t_status *stat)
{
    //pipe_first_last(s, stat);
    (void) s;
    unterminated_quotes(*tokens, stat);
    redir_as_end(*tokens, stat);
    multi_pipe(*tokens, stat);
    multi_adjacent_symbols(*tokens, stat);
    multi_redir(*tokens, stat);
}
