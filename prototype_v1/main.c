/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 15:44:43 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "OP_BRAC", "CL_BRAC", "AMP", "NONE"};

	char		*pipeline;
	t_token		*tok;

	pipeline = NULL;
	tok = NULL;
	//while (1)
	//{
		pipeline = readline("prompt> ");
		if (pipeline && *pipeline)
			add_history(pipeline);
		lexer(pipeline, &tok);
		free(pipeline);
		pipeline = NULL;
	//}
	
	for (t_token *dl = tok; dl != NULL; dl = dl->next)
		printf("\x1b[41m[%s]\x1b[m is of type %i which is \x1b[45m[%s]\x1b[m\n", dl->token, dl->symbol, type[dl->symbol]);
}
