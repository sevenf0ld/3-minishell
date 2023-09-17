/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/17 14:17:15 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int argc, char **argv)
{
	char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
	
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	/*
	//while (1)
	//{
		pipeline = readline("prompt> ");
		if (pipeline && *pipeline)
			add_history(pipeline);
		lexer(pipeline, &tok);
		free(pipeline);
		pipeline = NULL;
	//}
	*/
	if (argc != 2)
		return (1);
	
	lexer(argv[1], &tok);
	for (t_token *dl = tok; dl != NULL; dl = dl->next)
		printf("\x1b[44m[%s]\x1b[m is of type %i which is \x1b[36m[%s]\x1b[m\n", dl->token, dl->symbol, type[dl->symbol]);
		//printf("[%s] is a [%s]. end? \x1b[32m%s\x1b[m\n", dl->token, type[dl->symbol], dl->end?"true":"false");
	
	//parser(&tok, &cmd);
	//for (t_token *dl = tok; dl != NULL; dl = dl->next)
		//printf("\x1b[44m[%s]\x1b[m is of type %i which is \x1b[36m[%s]\x1b[m\n", dl->token, dl->symbol, type[dl->symbol]);
		//printf("[%s] is a [%s]. end? \x1b[32m%s\x1b[m\n", dl->token, type[dl->symbol], dl->end?"true":"false");
	
	parser(&tok, &cmd);
	
	//for (t_command *full = cmd; full != NULL; full = full->next)
		//printf("cmd set \x1b[33m%s\x1b[m\n", full->cmd);
	
	t_command *tmp;
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
	{
		printf("@ [%s]\n", tmp->cmd);
		if (tmp->flags != NULL)
		{
			printf("flags yes\n");
			for (int i = 0; i < tmp->num_f; i++)
				printf("--- {%s}\n", tmp->flags[i]);
		}
		if (tmp->args != NULL)
		{
			printf("args yes\n");
			for (int i = 0; i < tmp->num_a; i++)
				printf("::: {%s}\n", tmp->args[i]);
		}
	}
}
