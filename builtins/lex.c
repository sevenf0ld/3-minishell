/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:10:12 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 01:12:09 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void	parse(char **tokens, int (f)(char *s, char *t), t_list **head)
{
	int	i;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (!f(tokens[i], "|") || !f(tokens[i], ">") || !f(tokens[i], "<") \
			|| !f(tokens[i], ">>") || !f(tokens[i], "<<"))
		{
			if (*head == NULL)
				*head = sl_new((*head), tokens[i]);
			else
				sl_add_back(head, tokens[i]);
		}
	}
}

void	free_tokens(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

/*
 * ls -al | grep me > file1
 * [ls] [-al] [|] [grep] [me] [>] [file1]
 */
void	lexer(char *s, t_list **head)
{
	char	**tokens;

	tokens = ft_split(s, ' ');
	for (int k = 0; tokens[k] != NULL; k++)
		printf("[%s] ", tokens[k]);
	printf("\n");
	parse(tokens, ft_strcmp, head);
	//free_tokens(tokens); //heap use after free lol
}

int	main(void)
{
	char	*cmd_line;
	t_list	*head;

	cmd_line = NULL;
	head = NULL;
	//while (1)
	//{
		cmd_line = readline("prompt> ");
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		lexer(cmd_line, &head);
		free(cmd_line);
		cmd_line = NULL;
	//}
	t_list	*cur;
	for (cur = head; cur != NULL; cur = cur->next)
		printf("-> %s\n", cur->cmd);
}
