/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:48:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/17 12:05:24 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

bool    is_pipe(char a)
{
    fprintf(stderr, "is_pipe %c? %c\n", a, a == '|' ? 'y' : 'n');
    if  (a == '|')
        return (true);
    return (false);
}

bool    is_in_re(char a)
{
    if (a == 60)
        return (true);
    return (false);
}

bool    is_out_re(char a)
{
    if (a == 62)
        return (true);
    return (false);
}

bool    is_add(char *s, size_t i, size_t len)
{
    if (i + 1 >= len)
        return (false);
    if (is_out_re(s[i]) && is_out_re(s[i + 1]))
        return (true);
    return (false);
}

bool    is_hd(char *s, size_t i, size_t len)
{
    if (i + 1 >= len)
        return (false);
    if (is_in_re(s[i]) && is_in_re(s[i + 1]))
        return (true);
    return (false);
}

void    slot_in_token(t_token *t_node, char *s, t_status *stat, t_token **tokens, char *r)
{
    t_token *tmp;
    t_token *new;
    (void) tmp;
    (void) new;
    (void) tokens;

    tmp = t_node;
    new = NULL;
    new = token_new(s, stat);
    new->next = t_node;
    if (t_node->prev == NULL)
    {
        t_node->prev = new;
        *tokens = new;
    }
    else
    {
        new->prev = t_node->prev;
        t_node->prev->next = new;
        t_node->prev = new;
    }
    t_node->token = r;
    t_node->symbol = ANON;
}

void    separate_delim(char *s, t_token *t_node, t_token **tokens, t_status *stat)
{
    (void) s;
    (void) t_node;
    (void) tokens;
    (void) stat;

    size_t i;
    size_t  len;

    i = 0;
    len = ft_strlen(s);
    while (s[i] != '\0')
    {
        /*
        if (is_pipe(s[i]))
        {
            fprintf(stderr, "pipe: %c\n", s[i]);
            if (i > 0)
                slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int) ft_strlen(s)));
            else
                slot_in_token(t_node, ft_substr(s, 0, 1), stat, tokens, ft_substr(s, 1, (int) ft_strlen(s)));
            break ;
        }
        else if (is_add(s, i, len))
        {
            //fprintf(stderr, "add: %s\n", ft_substr(s, i, 2));
            if (i > 0)
                slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int) ft_strlen(s)));
            else
                slot_in_token(t_node, ft_substr(s, 0, 2), stat, tokens, ft_substr(s, 2, (int) ft_strlen(s)));
            break ;
        }
        else if (is_hd(s, i, len))
        {
            //if before hd
            fprintf(stderr, "   before hd (%zu): %s\n", i, ft_substr(s, 0, i));
            // wc, <<
            //slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , 2), i);
            // wc, <<LIM
            slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int)ft_strlen(s)), i);
            //hd symbol itself
            fprintf(stderr, "hd (%zu): %s\n", i, ft_substr(s, i, 2));
            i += 2;
            //if after hd
            fprintf(stderr, "   after hd (%zu): %s\n", i, s + i);
            if (i > 0)
                slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int) ft_strlen(s)));
            else
                slot_in_token(t_node, ft_substr(s, 0, 2), stat, tokens, ft_substr(s, 2, (int) ft_strlen(s)));
            break ;
        }
        else if (is_in_re(s[i]))
        {
            fprintf(stderr, "in_re: %c\n", s[i]);
            if (i > 0)
                slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int) ft_strlen(s)));
            else
                slot_in_token(t_node, ft_substr(s, 0, 1), stat, tokens, ft_substr(s, 1, (int) ft_strlen(s)));
            break ;
        }
        else if (is_out_re(s[i]))
        {
            fprintf(stderr, "out_re: %c\n", s[i]);
            if (i > 0)
                slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int) ft_strlen(s)));
            else
                slot_in_token(t_node, ft_substr(s, 0, 1), stat, tokens, ft_substr(s, 1, (int) ft_strlen(s)));
            break ;
        }
        */
        fprintf(stderr, "in2 %c\n", s[i]);
        if (is_hd(s, i, len) || is_add(s, i, len))
        {
            if (i > 0)
                slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int) ft_strlen(s)));
            else
                slot_in_token(t_node, ft_substr(s, 0, 2), stat, tokens, ft_substr(s, 2, (int) ft_strlen(s)));
            return ;
        }
        else if (is_pipe(s[i] || is_in_re(s[i]) || is_out_re(s[i])))
        {
            fprintf(stderr, "in\n");
            if (i > 0)
                slot_in_token(t_node, ft_substr(s, 0, i), stat, tokens, ft_substr(s, i , (int) ft_strlen(s)));
            else
                slot_in_token(t_node, ft_substr(s, 0, 1), stat, tokens, ft_substr(s, 1, (int) ft_strlen(s)));
            return ;
        }
        i++;
    }
}

size_t delim_present(char *s)
{
    size_t  i;
    size_t  len;

    i = 0;
    len = ft_strlen(s);
    if (s[0] == 39 || s[0] == 34)
        if (s[len - 1] == 39 || s[len - 1] == 34)
            return (0);
    while (s[i] != '\0')
    {
        if (is_delim(s[i]))
            return (1);
        i++;
    }
    return (0);
}

/*
   split the symbol(s) concatenated to other characters if q is false
   | > < >> <<
*/
void    split_tokens(t_token **tokens, t_status *stat)
{
    t_token *tmp;

    tmp = *tokens;
    while (tmp != NULL)
    {
        //function to check and split
        if (tmp->symbol == CMD || tmp->symbol == ARGS || tmp->symbol == FILN || tmp->symbol == LIM)
        {
            if (delim_present(tmp->token))
            {
                separate_delim(tmp->token, tmp, tokens, stat);
                t_token *cur = *tokens;
                while (cur != NULL)
                {
                    fprintf(stderr, "cur: %s\n", cur->token);
                    cur = cur->next;
                }
                tmp = tmp->prev;
                continue ;
            }
        }
        tmp = tmp->next;
    }
}
