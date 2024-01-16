/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:48:48 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/16 12:42:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

bool    is_pipe(char a)
{
    if  (a == 124)
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

void    slot_in_token(t_token *t_node, char *s, t_status *stat)
{
    t_token *tmp;
    t_token *bfr;
    t_token *aft;
    t_token *new;

    tmp = t_node;
    bfr = NULL;
    aft = NULL;
    new = NULL;
    if (tmp->prev != NULL)
        bfr = tmp->prev;
    if (tmp->next != NULL)
        aft = tmp->next;
    new = token_new(s, stat);
    if (bfr != NULL)
        bfr->next = new;
    new->next = aft;
}

void    separate_delim(char *s, t_token *t_node, t_token **tokens, t_status *stat)
{
    (void) s;
    (void) t_node;
    (void) tokens;
    //fprintf(stderr, "\x1b[32m potential issue\x1b[m %s\n", s);

    size_t i;
    size_t  len;

    i = 0;
    len = ft_strlen(s);
    while (s[i] != '\0')
    {
        fprintf(stderr, "\x1b[33m");
        if (is_pipe(s[i]))
        {
            fprintf(stderr, "pipe: %c\n", s[i]);
        }
        else if (is_add(s, i, len))
        {
            fprintf(stderr, "   before add: %s\n", ft_substr(s, 0, i));
            slot_in_token(t_node, ft_substr(s, 0, i), stat);
            fprintf(stderr, "add: %s\n", ft_substr(s, i, 2));
            i += 2;
            fprintf(stderr, "   after add: %s\n", s + i);
            continue ;
        }
        else if (is_hd(s, i, len))
        {
            fprintf(stderr, "   before hd: %s\n", ft_substr(s, 0, i));
            fprintf(stderr, "hd: %s\n", ft_substr(s, i, 2));
            i += 2;
            fprintf(stderr, "   after hd: %s\n", s + i);
            continue ;
        }
        else if (is_in_re(s[i]))
            fprintf(stderr, "in_re: %c\n", s[i]);
        else if (is_out_re(s[i]))
            fprintf(stderr, "out_re: %c\n", s[i]);
        fprintf(stderr, "\x1b[m");
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
            if (delim_present(tmp->token))
                separate_delim(tmp->token, tmp, tokens, stat);
        tmp = tmp->next;
    }
    
}
