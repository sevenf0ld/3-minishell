/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:37:27 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/20 07:24:14 by maiman-m         ###   ########.fr       */
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
                    return (redir_err(tmp->next->token, stat));
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
                return (redir_err(NULL, stat));
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
                        return (redir_err(">", stat));
                    else
                        return (symbols_err(stat));
                }
                i++;
            }
        }
        tmp = tmp->next;
    }
    return (0);
}

static void    decide_quote(char c, bool *sq, bool *wq)
{
    if (c == 39 && !*sq && !*wq)
        *sq = true;
    else if (c == 34 && !*wq && !*sq)
        *wq = true;
    else if (c == 39 && *sq && !*wq)
        *sq = false;
    else if (c == 34 && *wq && !*sq)
        *wq = false;
}

static int  unterm_q_norme(bool sq, bool wq, t_status *stat)
{
    if (sq && !wq)
        return (quote_err("\'", stat));
    else if (wq && !sq)
        return (quote_err("\"", stat));
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
                if (s[i] == 39 || s[i] == 34)
                    decide_quote(s[i], &sq, &wq);
                i++;
            }
            if (unterm_q_norme(sq, wq, stat))
                return (1);
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
        return (pipe_related_err(stat));
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
                return (pipe_related_err(stat));
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
