/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/10 22:17:09 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// int hrdc(char *pipeline)
// {
// 	int	i;
// 	int kw;

// 	i = 1;
// 	while (pipeline[++i])
// 	{
// 		if (pipeline[i + 1] == '<' && pipeline[i] == '<')
// 		{
// 			printf("Contain <<\n");
			
// 		}
// 	}
// 	printf("Doesn't contain\n");
// 	return (0);
// }

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
    	signal(SIGINT, sig_int);
		pipeline = readline("prompt> ");
		// hrdc(pipeline);
		if (!pipeline)
		{
			ft_putstr_fd("\bexit\n", STDIN_FILENO);
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
		free(pipeline);
		pipeline = NULL;
		printf("pipeline>>>>%s\n", pipeline);
	}
}
