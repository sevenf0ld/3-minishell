/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/04 16:43:15 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	//char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};


	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	while (1)
	{
		pipeline = readline("prompt> ");
		// printf("%s \n", pipeline);
		if (ft_strcmp(pipeline, ""))
			add_history(pipeline);
		lexer(pipeline, &tok);
		// for (t_token *dl = tok; dl != NULL; dl = dl->next)
		// 	printf("\x1b[44m[%s]\x1b[m is of type %i which is \x1b[36m[%s]\x1b[m [%d]\n", dl->token, dl->symbol, type[dl->symbol], dl->exp);
		parser(&tok, &cmd);
		t_command *tmp;

		tmp = cmd;
		cmd_ls(&tmp);
		for (tmp = cmd; tmp != NULL; tmp = tmp->next)
		{
			// printf("stdin %i overwrite %i append %i\n", tmp->num_si, tmp->num_so_o, tmp->num_so_a);
			// /*
			// printf("@ [%s]\n", tmp->cmd);
			if (tmp->flags != NULL)
			{
				//printf("flags yes\n");
				// for (int i = 0; i < tmp->num_f; i++)
					// printf("--- {%s}\n", tmp->flags[i]);
			}
			if (tmp->args != NULL)
			{
				//printf("args yes\n");
				// for (int i = 0; i < tmp->num_a; i++)
					// printf("::: {%s}\n", tmp->args[i]);
			}
		}
	}
}
