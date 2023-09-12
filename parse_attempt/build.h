/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:14:19 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/12 18:30:00 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_H
# define BUILD_H

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

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

//lexer
typedef struct s_token
{
	char				*token;
	struct s_token		*next;
}						t_token;			

//parser
typedef struct	s_command
{
	char				*cmd;
	char				**flags;
	char				**input;
	int					num_f;
	int					num_i;
	int					std_in;
	int					std_out;
	int					std_err;
	int					order;
	struct s_command	*next;
}						t_command;

//setter
typedef struct	s_split
{
	char			*each;
	t_type			symbol;
	struct s_split	*next;
}					t_split;

/*	LEXER	*/
//lex.c
void		lexer(char *s, t_token **tokens, t_command **cmds);

//init_token.c
t_token		*token_new(char *token);
void		token_add_back(t_token **head, t_token *node);
void		token_init(char **args, t_token **head);
t_token		*token_last(t_token *head);
int			token_size(t_token *head);

/*	PARSER	*/
//parse.c
void		set_cmd(char **full_cmd, t_command **c_node);
void		parser(t_token **tokens, t_command **cmds);

//init_cmd.c
t_command	*cmd_new(void);
void		cmd_add_back(t_command **head, t_command *node);
void		cmd_init(char **args, t_command **head);
t_command	*cmd_last(t_command *head);
int			cmd_size(t_command *head);

/*	SETTER	*/
//set.c
void		set_split_type_one(t_split **splits, int (f)(char *s, char *t));
void		set_split_type_two(t_split **splits);

//init_split.c
t_split		*split_new(char *split);
void		split_add_back(t_split **head, t_split *node);
void		split_init(char **args, t_split **head);
t_split		*split_last(t_split *head);
int			split_size(t_split *head);

#endif
