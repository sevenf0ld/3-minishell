/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:02:33 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/14 16:29:55 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

/*
 * recognizes only $ for variable expansion
 * " "
 */
int	is_weak_quote(char a)
{
	if (a == 34)
		return (1);
	return (0);
}

/*
 * ignores all metacharacters
 * ' '
 */
int	is_strong_quote(char a)
{
	if (a == 39)
		return (1);
	return (0);
}

int	is_space(char a)
{
	if (a == 32)
		return (1);
	return (0);
}

/*
 * if space, don't care
 * if pipe, add new node
 * if quotes
 * 		if strong, ignore all
 * 		if weak, recognize only $
 */
void	meta(char *s, t_token **tokens)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *tokens;
	while (s[i] != '\0')
	{
		if (is_space(s[i]))
		{
			i++;
			continue ;
		}
		/*
		if (is_strong_quote(s[i]))
		{
			printf("%c", s[i++]);
			continue ;
		}
		if (is_weak_quote(s[i]))
		{
			printf("%c", s[i++]);
			continue ;
		}
		*/
		i++;
	}
}

int	main(void)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	//while (1)
	//{
		pipeline = readline("prompt> ");
		if (pipeline && *pipeline)
			add_history(pipeline);
		lexer(pipeline, &tok, &cmd);
		//meta(pipeline, &tok);
		free(pipeline);
		pipeline = NULL;
	//}
	t_token	*cur;
	for (cur = tok; cur != NULL; cur = cur->next)
		printf("-> %s\n", cur->token);

	t_command *tmp;
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
		printf("@ [%s]\n", tmp->cmd);
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
		for (int i = 0; i < tmp->num_f; i++)
			printf("--- {%s}\n", tmp->flags[i]);
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
		for (int i = 0; i < tmp->num_i; i++)
			printf("::: {%s}\n", tmp->input[i]);
}
