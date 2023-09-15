/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:01 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 13:56:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

/*
 * CMD 0
 * OPT 1
 * MSG 2
 * PIPE 3
 * OUTREDIR 4
 * INREDIR 5
 * ADDEND 6
 * HEREDOC 7
 * FILN 8
 */
typedef enum e_type
{
	CMD,
	OPT,
	MSG,
	PIPE,
	OUTREDIR,
	INREDIR,
	ADDEND,
	HEREDOC,
	FILN
}	t_type;

typedef struct s_token
{
	char			*token;
	t_type			symbol;
	struct s_token	*next;
}					t_token;

/*	TOKENIZER	*/
//tokenizer.c
char		**new_split(char *str, char *delim, size_t n);

//init_token.c
t_token		*token_new(char *token);
void		token_add_back(t_token **head, t_token *node);
void		token_init(char **args, t_token **head);
t_token		*token_last(t_token *head);
int			token_size(t_token *head);

/*	LEXER	*/
//lexer.c
void		lexer(char *pipeline, t_token **tokens);


#endif
