/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:01 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 16:09:48 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

/*
 * 0 PIPE
 * 1 >
 * 2 <
 * 3 "
 * 4 '
 * 5 (
 * 6 )
 * 7 &
 * 8 ANONYMOUS
 */
typedef enum e_type
{
	PIPE,
	OUT_RE,
	IN_RE,
	W_Q,
	S_Q,
	OP_BRAC,
	CL_BRAC,
	AMP,
	ANON
}	t_type;

typedef struct s_token
{
	char			*token;
	t_type			symbol;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

/*	TOKENIZER	*/
//tokenizer.c
char		**new_split(char *str);

//init_token.c
t_token		*token_new(char *token);
void		token_add_back(t_token **head, t_token *node);
void		token_init(char **args, t_token **head);
t_token		*token_last(t_token *head);
int			token_size(t_token *head);

//d_ll_convert.c
t_token		*double_ll_convert(t_token **lst);

/*	LEXER	*/
//lexer.c
int			mini_delim(char a);
void		categorize_tokens(t_token **tokens, int (f)(char *s, char *t));
void		lexer(char *pipeline, t_token **tokens);

#endif
