/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/16 18:46:01 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
	
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	while (1)
	{
		pipeline = readline("prompt> ");
		if (pipeline && *pipeline)
			add_history(pipeline);
		lexer(pipeline, &tok);
		for (t_token *dl = tok; dl != NULL; dl = dl->next)
			fprintf(stderr, "\x1b[44m[%s]\x1b[m is of type %i which is \x1b[36m[%s]\x1b[m\n", dl->token, dl->symbol, type[dl->symbol]);
		parser(&tok, &cmd);
		free(pipeline);
		pipeline = NULL;
	}
}
