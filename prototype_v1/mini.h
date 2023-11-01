/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:01 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/01 19:29:07 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>

/*
 * 0 PIPE
 * 1 >
 * 2 <
 * 3 "
 * 4 '
 * 5 COMMAND
 * 6 OPTIONS/FLAGS
 * 7 ARGUMENTS
 * 8 FILENAME
 * 9 LIMITER
 * 10 HEREDOC <<
 * 11 ADDEND >>
 * 12 ANONYMOUS (will remove)
 */
typedef enum e_sym
{
	PIPE,
	OUT_RE,
	IN_RE,
	W_Q,
	S_Q,
	CMD,
	OPT,
	ARGS,
	FILN,
	LIM,
	HD,
	ADD,
	ANON
}	t_sym;

typedef struct s_token
{
	char			*token;
	t_sym			symbol;
	bool			end;
	bool			rm;
	bool			exp;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

/*
 * iterate over the t_token until end is set to true
 * set the lim or stdx_re accordingly
 * remove the nodes
 *
 * how to handle quotes?
 * (for bonus, how to know handle LAND or LOR?)
 */
typedef struct s_command
{
	int					pos;
	int					size;
	char				*cmd;
	char				**flags;
	int					num_f;
	char				**args;
	int					num_a;
	char				*lim;
	int					*std_in;
	int					num_si;
	int					*std_out_o;
	int					num_so_o;
	int					*std_out_a;
	int					num_so_a;
	int					pipe_fd[2];
	struct s_command	*next;
}						t_command;

/*	TOKENIZER	*/
//tokenizer.c
char		**new_split(char *str);

//tokenizer_utils.c
int			is_delim(char a);
char		*handle_spaces_btwn_q(char a, char c);
char		**init_split_pipeline(char *s, int w_c);

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
void		categorize_symbol(t_token **tokens);
void		categorize_params(t_token **tokens);
void		categorize_params_norme(t_token **tokens);
void		categorize_cmdwflags(t_token **tokens);
void		lexer(char *pipeline, t_token **tokens);

//lexer_utils.c
void		identify_symbols(t_token **tokens);
void		group_cmds(t_token **tokens);

//lexer_utils2.c
void		manage_quotes(t_token **tokens);
void		delete_quotes_after_expand(t_token **tokens, t_sym symbol);

//lexer_utils3.c
void		expansion(t_token **lst);

/*	PARSER	*/
//parser.c
void		parser(t_token **tokens, t_command **cmds);
void		complete_cmd(t_token **tokens, t_command **cmds);
void		init_multi_fa(t_token **tokens, t_command *c_node);

//parser_utils.c
void		init_multi_redir(t_token **tokens, t_command *c_node);

//parser_utils2.c
void		handle_redirections(t_command *c_node);

//parser_utils3.c
void		handle_pipe_ends(t_command *c_node);

//init_cmd.c
t_command	*cmd_new(char *cmd, int n);
void		cmd_add_back(t_command **head, t_command *node);
void		cmd_init(t_token **tokens, t_command **cmds);
t_command	*cmd_last(t_command *head);
int			cmd_size(t_command *head);

//err_handling.c
void		report_err(char *fn);
void		*malloc_err(size_t size);
int			open_err(char *file, int flags, mode_t mode);
void		dup2_err(int old_fd, int new_fd);
void		close_err(int fd);

#endif
