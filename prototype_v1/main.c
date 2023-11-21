/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/22 04:19:49 by maiman-m         ###   ########.fr       */
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
			{
				if (!cur->builtin)
					n_builtins(&cur);
				else if (!ft_strcmp(cur->cmd, "echo"))
					b_echo(cur);
			}
			dup2_err(restore_stdout, STDOUT_FILENO);
			close_err(restore_stdout);
			dup2_err(restore_stdin, STDIN_FILENO);
			close_err(restore_stdin);
		}
	}
}
