/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/25 09:40:25 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * use an array of cmds to make it shorter
 */
bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		return (true);
	else if (ft_strcmp(cmd, "cd"))
		return (true);
	else if (ft_strcmp(cmd, "pwd"))
		return (true);
	else if (ft_strcmp(cmd, "export"))
		return (true);
	else if (ft_strcmp(cmd, "unset"))
		return (true);
	else if (ft_strcmp(cmd, "env"))
		return (true);
	else if (ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

int	main(int argc, char **argv, char **envp)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	t_env		*env;
	t_fixed		*fix;
	int			restore_stdout;
	int			restore_stdin;

	pipeline = NULL;
	// signal(SIGINT, sig_int);
	// signal(SIGQUIT, sig_quit);
	tok = NULL;
	cmd = NULL;
	env = NULL;
	fix = NULL;
	(void) argc;
	(void) argv;
	f_init(&fix, envp);
	env_init(&env, envp, fix);
	while (1)
	{
		// ft_putstr_fd("minishell > ", STDERR_FILENO);
		// pipeline = get_next_line(0);
		// if (pipeline == NULL)
		// {
		// 	ft_putstr_fd("\b exit\n", STDERR_FILENO);
		// 	return (0);
		// }
		// printf("%s", pipeline);
		pipeline = readline("prompt> ");
		if (!pipeline)
		{
			printf("exit\n");
			exit(1);
		}
		else if (ft_strcmp(pipeline, ""))
		{
			add_history(pipeline);
			lexer(pipeline, &tok);
			restore_stdout = dup_err(STDOUT_FILENO);
			restore_stdin = dup_err(STDIN_FILENO);
			parser(&tok, &cmd, env);
			for (t_command *cur = cmd; cur != NULL; cur = cur->next)
			{
				if (!cur->builtin)
					n_builtins(&cur);
				else if (!ft_strcmp(cur->cmd, "echo"))
					b_echo(cur);
				else if (!ft_strcmp(cur->cmd, "pwd"))
					b_pwd('w');
				else if (!ft_strcmp(cur->cmd, "cd"))
					b_cd(cur);
				else if (!ft_strcmp(cur->cmd, "env"))
					b_env(&fix);
				else if (!ft_strcmp(cur->cmd, "unset"))
					b_unset(cur, &fix);
				else if (!ft_strcmp(cur->cmd, "export"))
					b_export(cur, &fix);
			}
			dup2_err(restore_stdout, STDOUT_FILENO);
			close_err(restore_stdout);
			dup2_err(restore_stdin, STDIN_FILENO);
			close_err(restore_stdin);
		}
	}
}
/*
int	main(int argc, char **argv)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
	if (argc != 2)
		return (1);
	lexer(argv[1], &tok);
	for (t_token *dl = tok; dl != NULL; dl = dl->next)
		printf("[%s] is a [%s]. remove? \x1b[32m%s\x1b[m\n", dl->token, type[dl->symbol], dl->rm?"true":"false");
	parser(&tok, &cmd);
	t_command *tmp;
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
	{
		printf("@ [%s]\n", tmp->cmd);
		if (tmp->flags != NULL)
		{
			for (int i = 0; i < tmp->num_f; i++)
				printf("--- {%s}\n", tmp->flags[i]);
		}
		if (tmp->args != NULL)
		{
			for (int i = 0; i < tmp->num_a; i++)
				printf("::: {%s}\n", tmp->args[i]);
		}
	}
}
*/
