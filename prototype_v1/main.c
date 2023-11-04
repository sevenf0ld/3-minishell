/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/04 17:11:53 by folim            ###   ########.fr       */
=======
/*   Updated: 2023/11/04 19:16:55 by maiman-m         ###   ########.fr       */
>>>>>>> testing
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	int			restore_stdout;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	while (1)
	{
		pipeline = readline("prompt> ");
		if (ft_strcmp(pipeline, ""))
		{
			restore_stdout = dup_err(STDOUT_FILENO);
			add_history(pipeline);
			lexer(pipeline, &tok);
			parser(&tok, &cmd);
			n_builtins(&cmd);
			dup2_err(restore_stdout, STDOUT_FILENO);
			close_err(restore_stdout);
		}
	}
}
