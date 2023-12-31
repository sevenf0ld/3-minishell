/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:01 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/30 17:10:25 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

// # include "libft.h"
# include "libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>

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
	bool			enclosed;
        struct s_status *stat;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

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
	int					*std_in; // <
	int					num_si;
	int					*std_out_o; // >
	int					num_so_o;
	int					*std_out_a; // >>
	int					num_so_a;
	int					read_end;
	int					write_end;
	char				*og;
	bool				builtin;
	int				last_out;
	struct s_env		*env_var;
	struct s_status		*stat;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_pipe
{
	int				pos;
	int				pipe_fd[2];
	struct s_pipe	*prev;
	struct s_pipe	*next;
}					t_pipe;

//add a field s_env *fixed which is a copy of the initialized list to make it cleaner
typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_fixed	*fixed;
	struct s_env	*next;
}					t_env;

//maybe only PATH is neccessary
//maybe only keep builtins paths
typedef struct	s_fixed
{
	char			*fkey;
	char			*fvalue;
	struct s_fixed	*fnext;
}					t_fixed;

typedef struct	s_status
{
	int	s_code;
}		t_status;

typedef struct  s_restore
{
        int     std_out;
        int     std_in;
}               t_restore;

/*	TOKENIZER	*/
//tokenizer.c
char		**new_split(char *str, t_status *stat);

//tokenizer_utils.c
int			is_delim(char a);
char		*handle_spaces_btwn_q(char a, char c);
char		**init_split_pipeline(char *s, int w_c, t_status *stat);

//init_token.c
t_token		*token_new(char *token, t_status *stat);
void		token_add_back(t_token **head, t_token *node);
void		token_init(char **args, t_token **head, t_status *stat);
t_token		*token_last(t_token *head);
int			token_size(t_token *head);

//d_ll_convert.c
t_token		*double_ll_convert(t_token **lst);
t_command	*double_ll_convert2(t_command **lst);
t_pipe		*double_ll_convert3(t_pipe **lst);

/*	LEXER	*/
//lexer.c
void		categorize_symbol(t_token **tokens);
void		categorize_params(t_token **tokens);
void		categorize_params_norme(t_token **tokens);
void		categorize_cmdwflags(t_token **tokens);
void		lexer(char *pipeline, t_token **tokens, t_status *stat);

//lexer_utils.c
void		identify_symbols(t_token **tokens);
void		group_cmds(t_token **tokens);

//lexer_utils2.c
void		manage_quotes(t_token **tokens);
void		reject_unterminated_q(t_token **tokens, t_sym symbol, t_status *stat);
void		delete_quotes_after_expand(t_token **tokens, t_sym symbol);

//lexer_utils3.c
void		expansion(t_token **lst, t_status *stat);

//lexer_utils4.c
t_token		*get_first_quote(t_token **tokens, t_sym symbol);
t_token		*get_last_quote(t_token **tokens, t_sym symbol);
void		double_check_quotes(t_token **tokens, t_sym symbol);

/*	PARSER	*/
//parser.c
void		init_multi_fa(t_token **tokens, t_command *c_node);
void		complete_cmd(t_token **tokens, t_command **cmds);
void		parser(t_token **tokens, t_command **cmds, t_env *envs, t_status *stat);

//parser_utils.c
void		init_multi_redir(t_token **tokens, t_command *c_node);
void		set_delimiter(t_token **tokens, t_command *c_node);

//parser_utils2.c
void		assign_pipe_ends(t_command *c_node, t_pipe *p_node);

//parser_utils3.c
void		redirect_command_io(t_command *c_node);

//init_cmd.c
t_command	*cmd_new(char *cmd, int n, t_env *envs, t_status *stat);
void		cmd_add_back(t_command **head, t_command *node);
void		cmd_init(t_token **tokens, t_command **cmds, t_env *envs, t_status *stat);
t_command	*cmd_last(t_command *head);
int			cmd_size(t_command *head);

//init_pipe.c
t_pipe		*pipe_new(int n, t_status *stat);
t_pipe		*pipe_last(t_pipe *head);
void		pipe_add_back(t_pipe **head, t_pipe *node);
void		pipe_init(t_pipe **pipes, int loop, t_status *stat);

/*	ERROR AND MEMORY HANDLER	*/
//err_handling.c
void		report_err(char *fn, int flag, t_status *stat);
void		*malloc_err(size_t size, t_status *stat);
int			open_err(char *file, int flags, mode_t mode, t_status *stat);
void		dup2_err(int old_fd, int new_fd, t_status *stat);
void		close_err(int fd, t_status *stat);
void		quote_err(t_status *stat);
void		pipe_err(int *pipe_arr, t_status *stat);
int			dup_err(int old_fd, t_status *stat);

//free.c
void		free_2d_arr(char **input);

/*	NON-BUILTINS EXECUTOR	*/
//command=ls.c
void		n_builtins(t_command **a, t_status *stat);
// void		cmd_ls_attach(int c);

/*	SIGNAL HANDLER	*/
//signal.c
void sig_int(int signum);
void sig_quit(int signum);

/*	BUILTINS EXECUTOR	*/
//b_echo.c
void		b_echo(t_command *c_node);

//b_dir.c
char		*b_pwd(t_command *c_node, char mode);
void		b_cd(t_command *c_node);

//b_environ.c
//void		b_env(t_command *c_node);
void		b_env(t_command *c_node, t_fixed **f_node);
void		b_unset(t_command *c_node, t_fixed **f_node);
void		b_export(t_command *c_node, t_fixed **f_node);

//b_exit.c
void		b_exit(t_command *c_node);

/*	ENVIRONMENT VARIABLES HANDLER	*/
//init_env.c
t_env		*env_new(char *var, t_fixed *f, t_status *stat);
t_env		*env_last(t_env *head);
void		env_add_back(t_env **head, t_env *node);
void		env_init(t_env **envs, char **envp, t_fixed *f, t_status *stat);

//init_fixed.c
t_fixed		*f_new(char *var, t_status *stat);
t_fixed		*f_last(t_fixed *head);
void		f_add_back(t_fixed **head, t_fixed *node);
void		f_init(t_fixed **envs, char **envp, t_status *stat);

#endif
