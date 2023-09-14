/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:10:12 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/14 12:02:53 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

/*
 * ls -la | cat | grep -wn c > outfile
 * # [ls] [-la] [|] [cat] [|] [grep] [-wn] [c] [>] [outfile]
 * [ ls -la ] [ cat ] [ grep -wn c > outfile]
 */
void	lexer(char *s, t_token **tokens, t_command **cmds)
{
	char	**word;

	word = ft_split(s, '|');
	
	for (int k = 0; word[k] != NULL; k++)
		printf("[%s] ", word[k]);
	for (int k = 0; word[k] != NULL; k++)
	{
		for (int l = 0; word[k][l] != '\0'; l++)
		{
			if (word[k][l] == 32)
			{
				printf("#");
				continue ;
			}
			printf("%c", word[k][l]);
		}
	}
	
	printf("\n");

	token_init(word, tokens);
	cmd_init(word, cmds);
	//free word
	parser(tokens, cmds);
}
