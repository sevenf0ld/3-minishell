/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:03:45 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/09 22:31:44 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

/*
 * might need to malloc
 */
void	builtin_pwd(void)
{
	char	*buffer;
	char	*pwd;

	buffer = NULL;
	pwd = getcwd(buffer, 0);
	printf("%s\n", pwd);
}

int	main(void)
{

	static	char	*cmd_line = NULL;
	while (1)
	{
		if (cmd_line)
		{
			free(cmd_line);
			cmd_line = NULL;
		}
		cmd_line = readline("prompt> ");
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		if (ft_strcmp(cmd_line, "pwd") == 0)
			builtin_pwd();
	}
}
