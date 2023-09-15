/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:01 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 16:38:09 by maiman-m         ###   ########.fr       */
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
 * 8 ANONYMOUS (will remove)
 */
typedef enum e_sym
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
}	t_sym;

/*
 * 0 COMMAND
 * 1 FLAGS/OPTIONS
 * 2 ARGUMENTS
 * 3 FILENAME
 * 4 NONE (will remove)
 */
typedef enum e_par
{
	CMD,
	OPT,
	ARGS,
	FILN,
	NONE
}	t_par;

typedef struct s_token
{
	char			*token;
	t_sym			symbol;
	t_par			param;
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
void		categorize_token_symbol(t_token **tokens, int (f)(char *s, char *t));
void		categorize_token_param(t_token **tokens);
void		lexer(char *pipeline, t_token **tokens);

#endif
