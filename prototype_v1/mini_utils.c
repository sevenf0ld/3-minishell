/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:50 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 14:39:06 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*join_and_free(char *to_free, char *to_concat)
{
	char	*end;

	end = ft_strjoin(to_free, to_concat);
	free(to_free);
	to_free = NULL;
	return (end);
}

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
