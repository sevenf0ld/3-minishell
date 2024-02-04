/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:20:01 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 00:01:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include "libft/include/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define IN_RE_FLAG O_RDONLY
# define OUT_RE_FLAG (O_CREAT | O_WRONLY | O_TRUNC)
# define ADD_FLAG (O_CREAT | O_WRONLY | O_APPEND)

/*
 * 0 PIPE
 * 1 >
 * 2 <
 * 3 COMMAND
 * 4 ARGUMENTS
 * 5 FILENAME
 * 6 LIMITER
 * 7 HEREDOC <<
 * 8 ADDEND >>
 * 9 ANONYMOUS
*/
typedef enum e_sym
{
	PIPE,
	OUT_RE,
	IN_RE,
	CMD,
	ARGS,
	FILN,
	LIM,
	HD,
	ADD,
	ANON
}						t_sym;

typedef struct s_token
{
	char				*token;
	t_sym				symbol;
	bool				end;
	bool				rm;
	bool				exp;
	struct s_status		*stat;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	int					pos;
	int					size;
	char				*cmd;
	char				**args;
	int					num_a;
	char				**lim;
	int					num_l;
	int					*std_in;
	int					num_si;
	int					*std_out_o;
	int					num_so_o;
	int					*std_out_a;
	int					num_so_a;
	int					read_end;
	int					write_end;
	char				*og;
	bool				builtin;
	int					last_out;
	bool				exec;
	struct s_env		*env_var;
	struct s_status		*stat;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_pipe
{
	int					pos;
	int					pipe_fd[2];
	struct s_pipe		*prev;
	struct s_pipe		*next;
}						t_pipe;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_fixed		*fixed;
	struct s_env		*next;
}						t_env;

typedef struct s_fixed
{
	char				*fkey;
	char				*fvalue;
	struct s_fixed		*fnext;
}						t_fixed;

typedef struct s_status
{
	int					s_code;
}						t_status;

typedef struct s_restore
{
	int					std_out;
	int					std_in;
}						t_restore;

typedef struct s_pid
{
	pid_t				*pid_c;
}						t_pid;

typedef struct s_mini
{
	t_sym				*sym;
	t_token				*tok;
	t_token				*tok_cpy;
	t_command			*cmd;
	t_pipe				*pip;
	t_env				*env;
	t_fixed				*fix;
	t_status			*stat;
	t_restore			*res;
	t_pid				*pid;
	int					piping;
	int					limiting;
        char                            *pipeline;
}						t_mini;

typedef struct s_sig
{
	bool				sig;
	int					sig_code;
}						t_sig;

extern t_sig			g_sig;

typedef struct s_cmd_norme
{
	int					i;
	t_token				*tmp;
	t_token				*first;
	t_token				**tokens;
	t_command			**cmds;
	t_env				*envs;
	t_status			*stat;
}						t_cmd_norme;

typedef struct s_fildes_norme
{
	t_token				**tokens;
	t_command			*c_node;
	t_token				*tmp;
	int					i;
	int					j;
	int					k;
}						t_fildes_norme;

typedef struct s_unterm_norme
{
	int					i;
	bool				sq;
	bool				wq;
	char				*s;
	t_token				*tmp;
}						t_unterm_norme;

typedef struct s_token_norme
{
	char				*s;
	t_token				**tokens;
	t_status			*stat;
	bool				sq;
	bool				wq;
	int					i;
	int					close;
	int					check;
	int					start;
	int					count;
	char				*sub;
}						t_token_norme;

typedef struct s_exp_norme
{
	bool				sq;
	bool				wq;
	int					close;
	char				*part;
	char				*s;
}						t_exp_norme;

typedef struct s_repl_norme
{
	char				*og;
	char				*displace;
	char				*sub;
	int					len_og;
	int					len_dis;
	int					len_sub;
	int					occur;
	char				*shift;
	char				*extracted;
	int					diff;
	char				*ret;
	char				*tmp;
	int					moved;
}						t_repl_norme;

/*      MINISHELL       */
//main.c
void					execution(t_mini *mi);
void					minishell(t_mini *mi, int flag);

//init_mini.c
void					mini_init_stat_res(t_mini *mi);
void					mini_init_environ(t_mini *mi, char **envp);
void					mini_init_pid(t_mini *mi);
void                                    mini_init_pipeline(t_mini *mi, char *s);

//mini_utils.c
void					save_io(t_mini *mi);
void					no_fork_b_exec(t_mini *mi, t_command *cur);
void					restore_io(t_mini *mi);

//mini_utils2.c
bool					is_builtin(char *cmd);
int						all_whitespace(char *s);
void					categorize(t_token **tokens);
char					*join_and_free(char *to_free, char *to_concat);
int						contain_quotes(char *s);

/*	TOKENIZER	*/
//tokenizer.c
void					within_alongside_quotes(t_token_norme *token_params,
							char *s, char mode);
void					tokenizer(char *str, t_token **tokens, t_status *stat);

//tokenizer_utils.c
int						is_delim(char a);
int						decide_chunk(t_token_norme *token_params, char *s);

//init_token.c
t_token					*token_new(char *token, t_status *stat);
void					token_add_back(t_token **head, t_token *node);
void					token_init(char *s, t_token **head, t_status *stat,
							int i);
t_token					*token_last(t_token *head);
int						token_size(t_token *head);

//d_ll_convert.c
t_token					*double_ll_convert(t_token **lst);
t_command				*double_ll_convert2(t_command **lst);
t_pipe					*double_ll_convert3(t_pipe **lst);

/*	LEXER	*/
//lexer.c
void					categorize_symbol(t_token **tokens);
void					categorize_params(t_token **tokens);
void					categorize_cmd_w_args(t_token **tokens);
int						lexer(char *pipeline, t_mini *mi);

//split.c
void					split_tokens(t_token **tokens);

//split_utils.c
bool					is_pipe(char a);
bool					is_in_re(char a);
bool					is_out_re(char a);
bool					is_add(char *s, size_t i, size_t len);
bool					is_hd(char *s, size_t i, size_t len);

//split_utils2.c
void					slot_in_token(t_token *t_node, char *s,
							t_token **tokens, char *r);
size_t					delim_present(char *s);
void					separate_delim(char *s, t_token *t_node,
							t_token **tokens);

//reject.c
int						pipe_first_last(t_token *t_node, t_status *stat);
int						multi_pipe(t_token *t_node, t_status *stat);
int						reject(t_token **tokens, t_status *stat);

//reject_utils.c
int						multi_redir(t_token *t_node, t_status *stat);
int						redir_as_end(t_token *t_node, t_status *stat);
int						multi_adjacent_symbols(t_token *t_node, t_status *stat);

//reject_utils2.c
int						unterminated_quotes(t_token *t_node, t_status *stat);

//expand.c
void					expansion(t_token **tokens, t_mini *mi);

//expand_utils.c
void					expand_utils(char **token, t_mini *mi);

//expand_utils2.c
void					set_bfr_exp(char **bfr, char *ref);
void					set_aft_exp(char **aft, char *ref);

//expand_utils3.c
void					sub_exp(char **sub, char *ref, t_mini *mi);

//expand_utils4.c
void					check_free_and_null(char **s);
void					reform_word(char **s, char **t, char **u, char **v);
void					till_dollar(char *s, int *i, int *in_quote);

//expand_utils5.c
int						contain_expandable(char *s);

//replace.c
char					*repl(char *og, char *displace, char *sub, int len_og);

//lexer_utils.c
void					group_cmds(t_token **tokens);

//delete.c
void                                    delete_all_element(t_token **lst, char *value);

/*	PARSER	*/
//parser.c
void					complete_cmd(t_mini *mi, t_token **tokens,
							t_command **cmds);
//void                                    update_cmd_exec(t_command **cmds);
void                                    update_cmd_exec(t_command *c_node);
void					parser(t_mini *mi);

//init_cmd.c
t_command				*cmd_new(char *cmd, int n, t_env *envs, t_status *stat);
void					cmd_add_back(t_command **head, t_command *node);
t_command				*cmd_last(t_command *head);
int						cmd_size(t_command *head);
void					set_cmd_size(t_command *head);

//init_cmd_utils.c
void					cmd_init(t_token **tokens, t_command **cmds,
							t_env *envs, t_status *stat);

//init_cmd_utils2.c
void					cmd_add_back(t_command **head, t_command *node);
t_command				*cmd_last(t_command *head);
int						cmd_size(t_command *head);
void					set_cmd_size(t_command *head);

//init_pipe.c
t_pipe					*pipe_new(int n, t_status *stat);
t_pipe					*pipe_last(t_pipe *head);
void					pipe_add_back(t_pipe **head, t_pipe *node);
void					pipe_init(t_pipe **pipes, int loop, t_status *stat);

//parser_utils.c
void					init_multi_redir(t_token **tokens, t_command *c_node);

//parser_utils2.c
void					assign_pipe_ends(t_command *c_node, t_pipe *p_node);

//parser_utils3.c
void					redirect_command_io(t_command *c_node);

//parser_utils4.c
void					count_enclosed(char *s, int *size);
void					init_enclosed_extract(char **ext, int size);
void					extract_enclosed(char *s, char *ext);

//parser_utils5.c
void					init_multi_a(t_token **tokens, t_command *c_node);
void					init_multi_l(t_mini *mi, t_token **tokens,
							t_command *c_node);

//parser_utils6.c
void					remove_quotes(char **args);
void					rm(char **args, int n);

/*      HEREDOC     */
//heredoc.c
void					heredoc(t_command *c_node, t_status *stat);

/*	NON-BUILTINS EXECUTOR	*/
//n_builtins.c
void					fork_exec(t_command *c_node, t_mini *mi);

//n_builtins_utils.c
int						mini_exec(t_command *c_node, t_mini *mi, char **envp);

//gnl.c
char					*get_next_line(int fd);
char					*read_and_store(char *store, int fd, char *buffer);
char					*extract_newline(char *store);
char					*update_store(char *store);
int						look_for_nl(char *to_search);

//concurrent.c
void					close_unused_ends(t_command **cmds, int i);
void					last_close(t_pipe **pipes, t_mini *mi);
void					close_and_wait(t_mini *mi);

/*	SIGNAL HANDLER	*/
//signal_parent.c
void					signal_parent(void);

//signal_child.c
void					signal_child(void);

/*	BUILTINS EXECUTOR	*/
//b_echo.c
void					b_echo(t_command *c_node, t_mini *mi);

//b_dir.c
char					*b_pwd(t_command *c_node, char mode, t_mini *mi);
void					b_cd(t_command *c_node, t_mini *mi);

//b_unset_env.c
void					b_env(t_command *c_node, t_fixed **f_node, t_mini *mi);
void					b_unset(t_command *c_node, t_fixed **f_node,
							t_mini *mi);

//b_export.c
void					b_export(t_command *c_node, t_fixed **f_node,
							t_mini *mi);

//b_exit.c
void					b_exit(t_command *c_node, t_mini *mi);

/*	ENVIRONMENT VARIABLES HANDLER	*/
//init_env.c
t_env					*env_new(char *var, t_fixed *f, t_status *stat);
t_env					*env_last(t_env *head);
void					env_add_back(t_env **head, t_env *node);
void					env_init(t_env **envs, char **envp, t_fixed *f,
							t_status *stat);

//init_fixed.c
t_fixed					*f_new(char *var, t_status *stat, int flag);
t_fixed					*f_last(t_fixed *head);
void					f_add_back(t_fixed **head, t_fixed *node);
void					f_init(t_fixed **envs, char **envp, t_status *stat);

//fixed_utils.c
char					*get_fvalue(t_fixed *f_node, char *fkey);
void					update_fvalue(t_fixed **fix, char *fkey, char *fval);
char					*get_oldpwd(t_fixed *f_node);

/*	ERROR AND MEMORY HANDLER	*/
//err_handling.c
void					report_err(char *fn, int flag, t_status *stat);
void					*malloc_err(size_t size, t_status *stat);
int						lim_err(char *file, int flags, mode_t mode,
							t_status *stat);
int						open_err(char *file, int flags, mode_t mode,
							t_command *c_node);
void					dup2_err(int old_fd, int new_fd, t_status *stat);

//err_handling_utils.c
void					close_err(int fd, t_status *stat);
int						quote_err(char *a, t_status *stat);
void					pipe_err(int *pipe_arr, t_status *stat);
int						dup_err(int old_fd, t_status *stat);
int						redir_err(char *token, t_status *stat);

//err_handling_utils2.c
int						symbols_err(t_status *stat);
int						pipe_related_err(t_status *stat);
int						path_err(t_command *c_node, int flag, t_status *stat);
void					export_err(char *err_arg, t_mini *mi);

//free.c
void					free_2d_arr(char **input);
void					free_tcmd(t_mini *mi);
void					free_ttkn(t_token **tkn);
void					free_tpipe(t_pipe **pipe);
void					garbage_burner(t_mini *mi);
void					print_tfix(t_fixed **tfix);

//free2.c
void					free_stat(t_status *status);
void					free_res(t_restore *res);
void					free_fix(t_fixed **fixed);
void					free_env(t_env **env);

#endif
