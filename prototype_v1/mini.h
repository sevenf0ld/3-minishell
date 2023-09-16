/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:01 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/16 17:38:15 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>

/*
 * 0 PIPE
 * 1 >
 * 2 <
 * 3 "
 * 4 '
 * 5 (
 * 6 )
 * 7 &
 * 8 COMMAND
 * 9 OPTIONS/FLAGS
 * 10 ARGUMENTS
 * 11 FILENAME
 * 12 LIMITER
 * 13 HEREDOC <<
 * 14 ADDEND >>
 * 15 LOGICAL OR ||
 * 16 LOGICAL AND &&
 * 17 ANONYMOUS (will remove)
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
	CMD,
	OPT,
	ARGS,
	FILN,
	LIM,
	HD,
	ADD,
	LOR,
	LAND,
	ANON
}	t_sym;

typedef struct s_token
{
	char			*token;
	t_sym			symbol;
	bool			end;
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
void		categorize_symbol(t_token **tokens, int (f)(char *s, char *t));
void		categorize_params(t_token **tokens);
void		categorize_params_norme(t_token **tokens);
void		categorize_cmdwflags(t_token **tokens);
void		lexer(char *pipeline, t_token **tokens);

//lexer_utils.c
void		identify_symbols(t_token **tokens);
void		group_cmds(t_token **tokens);

//lexer_bonus.c
void		handle_bonus_symbols(t_token **tokens);

/*	PARSER	*/
//parser.c

#endif
