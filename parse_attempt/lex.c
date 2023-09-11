/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:10:12 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/11 16:19:54 by maiman-m         ###   ########.fr       */
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

int	main(void)
{
	char		*cmd_line;
	t_token		*tok;
	t_command	*cmd;

	cmd_line = NULL;
	tok = NULL;
	cmd = NULL;
	//while (1)
	//{
		cmd_line = readline("prompt> ");
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		lexer(cmd_line, &tok, &cmd);
		free(cmd_line);
		cmd_line = NULL;
	//}
	t_token	*cur;
	for (cur = tok; cur != NULL; cur = cur->next)
		printf("-> %s\n", cur->token);
	t_command *tmp;
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
		printf("@ [%s]\n", tmp->cmd);
	//for (tmp = cmd; tmp != NULL; tmp = tmp->next)
		//printf("- [%s]\n", tmp->flags);
	//for (tmp = cmd; tmp != NULL; tmp = tmp->next)
		//printf(": [%s]\n", tmp->input);
}
