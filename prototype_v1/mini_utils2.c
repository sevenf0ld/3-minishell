/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:14:15 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 16:52:16 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * use an array of cmds to make it shorter
 */
bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "echo"))
		return (true);
	else if (!ft_strcmp(cmd, "cd"))
		return (true);
	else if (!ft_strcmp(cmd, "pwd"))
		return (true);
	else if (!ft_strcmp(cmd, "export"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	else if (!ft_strcmp(cmd, "env"))
		return (true);
	else if (!ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

int	all_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_iswhite(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	categorize(t_token **tokens)
{
	categorize_symbol(tokens);
	categorize_params(tokens);
	categorize_cmd_w_args(tokens);
}

char	*join_and_free(char *to_free, char *to_concat)
{
	char	*end;

	end = ft_strjoin(to_free, to_concat);
	free(to_free);
	to_free = NULL;
	return (end);
}

//static int	contain_quotes(char *s)
int	contain_quotes(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
