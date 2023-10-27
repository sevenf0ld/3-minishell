/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/27 19:03:07 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int argc, char **argv)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
/*
	while (1)
	{
		pipeline = readline("prompt> ");
		if (ft_strcmp(pipeline, ""))
			add_history(pipeline);
		lexer(pipeline, &tok);
		parser(&tok, &cmd);
		free(pipeline);
		pipeline = NULL;
	}
*/
	//char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
	if (argc != 2)
		return (1);

	lexer(argv[1], &tok);
	for (t_token *dl = tok; dl != NULL; dl = dl->next)
		;
		//printf("\x1b[44m[%s]\x1b[m is of type %i which is \x1b[36m[%s]\x1b[m [%d] end? end? \x1b[32m%s\x1b[m\n", dl->token, dl->symbol, type[dl->symbol], dl->exp, dl->end?"true":"false");

	parser(&tok, &cmd);
	t_command *tmp;
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
	{
		for (int j = 0; tmp->std_in != NULL && tmp->std_in[j] != INT_MIN; j++)
			printf("in_re fd %i\n", tmp->std_in[j]);
		for (int j = 0; tmp->std_out_o != NULL && tmp->std_out_o[j] != INT_MIN; j++)
			printf("out_re fd %i\n", tmp->std_out_o[j]);
		for (int j = 0; tmp->std_out_a != NULL && tmp->std_out_a[j] != INT_MIN; j++)
			printf("add fd %i\n", tmp->std_out_a[j]);
		/*
		printf("@ [%s]\n", tmp->cmd);
		if (tmp->flags != NULL)
		{
			//printf("flags yes\n");
			for (int i = 0; i < tmp->num_f; i++)
				printf("--- {%s}\n", tmp->flags[i]);
		}
		if (tmp->args != NULL)
		{
			//printf("args yes\n");
			for (int i = 0; i < tmp->num_a; i++)
				printf("::: {%s}\n", tmp->args[i]);
		}
		*/
	}
}
