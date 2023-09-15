/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 13:52:45 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
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
	
	t_token	*cur;
	for (cur = tok; cur != NULL; cur = cur->next)
		printf("-> %s\n", cur->token);
}
