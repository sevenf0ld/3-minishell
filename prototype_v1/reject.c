/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:37:27 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 15:56:48 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int multi_redir(t_token *t_node, t_status *stat)
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
                    return (1);
                }
        tmp = tmp->next;
    }
    return (0);
}

static int redir_as_end(t_token *t_node, t_status *stat)
{
    t_token *tmp;

    tmp = t_node;
    while (tmp != NULL)
    {
        if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE || tmp->symbol == ADD || tmp->symbol == HD)
            if (tmp->next == NULL || (tmp->next != NULL && tmp->next->symbol == PIPE))
            {
                redir_err(NULL, stat);
                return (1);
            }
        tmp = tmp->next;
    }
    return (0);
}

static int multi_adjacent_symbols(t_token *t_node, t_status *stat)
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
                    //symbols_err(stat);
                    //redir_err(&s[i + 1], stat);
                    if (s[i + 1] == '>')
                        redir_err(">", stat);
                    else
                        symbols_err(stat);
                    return (1);
                }
                i++;
            }
        }
        tmp = tmp->next;
    }
    return (0);
}

static int unterminated_quotes(t_token *t_node, t_status *stat)
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
            {
                quote_err("\'", stat);
                return (1);
            }
            else if (wq && !sq)
            {
                quote_err("\"", stat);
                return (1);
            }
        }
        tmp = tmp->next;
    }
    return (0);
}

static int pipe_first_last(t_token *t_node, t_status *stat)
{
    t_token *tmp;
    t_token *last;

    tmp = t_node;
    last = token_last(t_node);
    if (tmp->symbol == PIPE || last->symbol == PIPE)
    {
        pipe_related_err(stat);
        return (1);
    }
    return (0);
}

static int multi_pipe(t_token *t_node, t_status *stat)
{
    t_token *tmp;

    tmp = t_node;
    while (tmp != NULL)
    {
        if (tmp->symbol == PIPE)
        {
            if (tmp->next != NULL && tmp->next->symbol == PIPE)
            {
                pipe_related_err(stat);
                return (1);
            }
        }
        tmp = tmp->next;
    }
    return (0);
}

/*
   ╰ pipe as the first or last node
   ╰ unterminated quotes
        ╰ single quote
        ╰ double quote
   ╰ nothing after redirection symbol / redirection as the last node
   ╰ multiple adjacent symbols
        ╰ in one node (ARGS only)
        ╰ across multiple nodes (redirections and pipe)
*/
int reject(t_token **tokens, t_status *stat)
{
    if (pipe_first_last(*tokens, stat))
        return (1);
    if (unterminated_quotes(*tokens, stat))
        return (1);
    if (redir_as_end(*tokens, stat))
        return (1);
    if (multi_adjacent_symbols(*tokens, stat))
        return (1);
    if (multi_redir(*tokens, stat))
        return (1);
    if (multi_pipe(*tokens, stat))
        return (1);
    return (0);
}
