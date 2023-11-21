/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/22 02:40:52 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
int	main(void)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	int			restore_stdout;
	int			restore_stdin;

	pipeline = NULL;
	// signal(SIGINT, sig_int);
	// signal(SIGQUIT, sig_quit);
	tok = NULL;
	cmd = NULL;
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
			parser(&tok, &cmd);
			for (t_command *cur = cmd; cur != NULL; cur = cur->next)
				n_builtins(&cur);
			dup2_err(restore_stdout, STDOUT_FILENO);
			close_err(restore_stdout);
			dup2_err(restore_stdin, STDIN_FILENO);
			close_err(restore_stdin);
		}
	}
}
*/

int	main(int argc, char **argv)
{
	char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	if (argc != 2)
		return (1);
	lexer(argv[1], &tok);
	for (t_token *dl = tok; dl != NULL; dl = dl->next)
		printf("\x1b[44m[%s]\x1b[m is of type %i which is \x1b[36m[%s]\x1b[m [%d]\n", dl->token, dl->symbol, type[dl->symbol], dl->end);
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
