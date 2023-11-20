/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/21 00:19:43 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	int			restore_stdout;
	int			restore_stdin;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	while (1)
	{
		pipeline = readline("prompt> ");
		if (ft_strcmp(pipeline, ""))
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
