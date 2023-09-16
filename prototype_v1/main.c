/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/16 17:27:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int argc, char **argv)
{
	char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "OP_BRAC", "CL_BRAC", "AMP", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "LOR", "LAND", "ANON"};
	
	char	*pipeline;
	t_token	*tok;

	pipeline = NULL;
	tok = NULL;
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
		printf("\x1b[44m[%s]\x1b[m is of type %i which is \x1b[36m[%s]\x1b[m\n\n", dl->token, dl->symbol, type[dl->symbol]);
		//printf("[%s] is a [%s]. end? \x1b[32m%s\x1b[m\n", dl->token, type[dl->symbol], dl->end?"true":"false");
}
