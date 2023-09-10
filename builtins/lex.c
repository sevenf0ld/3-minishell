/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:10:12 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 22:56:15 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

void	set_token_type(t_token **tokens, int (f)(char *s, char *t))
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (!f(tmp->token, ">"))
			tmp->symbol = OUTREDIR;
		else if (!f(tmp->token, "<"))
			tmp->symbol = INREDIR;
		else if (!f(tmp->token, ">>"))
			tmp->symbol = ADDEND;
		else if (!f(tmp->token, "<<"))
			tmp->symbol = HEREDOC;
		else if (!f(tmp->token, "|"))
			tmp->symbol = PIPE;
		tmp = tmp->next;
	}
}

/*
 * ls -la | cat | grep -wn c > outfile
 * # [ls] [-la] [|] [cat] [|] [grep] [-wn] [c] [>] [outfile]
 * [ ls -la ] [ cat ] [ grep -wn c > outfile]
 * 		should trim the whitespaces
 */
void	lexer(char *s, t_token **tokens, t_command **cmds)
{
	char	**word;

	word = ft_split(s, '|');

	for (int k = 0; word[k] != NULL; k++)
		printf("[%s] ", word[k]);
	printf("\n");

	token_init(word, tokens);
	//set_token_type(tokens, ft_strcmp);
	cmd_init(word, cmds);
	//free word
	parser(tokens, cmds);
}

int	main(void)
{
	char		*cmd_line;
	t_token		*tokens_tok;
	t_command	*tokens_cmd;

	cmd_line = NULL;
	tokens_tok = NULL;
	tokens_cmd = NULL;
	//while (1)
	//{
		cmd_line = readline("prompt> ");
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		lexer(cmd_line, &tokens_tok, &tokens_cmd);
		free(cmd_line);
		cmd_line = NULL;
	//}
	t_token	*cur;
	for (cur = tokens_tok; cur != NULL; cur = cur->next)
		printf("-> %s\n", cur->token);
	t_command *tmp;
	for (tmp = tokens_cmd; tmp != NULL; tmp = tmp->next)
		printf("@ %s\n", tmp->cmd);
	for (tmp = tokens_cmd; tmp != NULL; tmp = tmp->next)
		printf("- %s\n", tmp->flags);
	for (tmp = tokens_cmd; tmp != NULL; tmp = tmp->next)
		printf(": %s\n", tmp->input);
}
