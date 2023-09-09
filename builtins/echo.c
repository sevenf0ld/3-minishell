/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:22:57 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/09 21:07:35 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

void	echo_var(char *s, char *var, void (*f)(char *s, int fd))
{
	int	i;
	if (ft_strncmp(s, var, ft_strlen(var)) == 0)
	{
		f(getenv(var + 1), STDOUT_FILENO);
		return ;
	}
	i = 0;
	while (ft_strncmp(s + i, var, ft_strlen(var)) != 0)
	{
		if (s[i] != 36)
			ft_putchar_fd(s[i++], STDOUT_FILENO);
	}
	f(getenv(var + 1), STDOUT_FILENO);
}

void	echo(char **to_echo, void (*f)(char *s, int fd), int i, bool nl)
{
	char	*var;
	while (to_echo[i] != NULL)
	{
		var = ft_strchr(to_echo[i], 36);
		if (var == NULL)
			f(to_echo[i], STDOUT_FILENO);
		else
			echo_var(to_echo[i], var, f);
		if (to_echo[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!nl)
		ft_putendl_fd("", STDOUT_FILENO);
}

/*
 * echo command writes its arguments separated by blanks and terminated by a newline on stdout
 * -n option included means no newline in the output
 *  based on length of first string else -nbullshit is regarded as a valid option
 *  funct ptrs in place of booleans and pass the initializer
 */
void	builtin_echo(char *s)
{
	char	**end;

	end = ft_split(s, ' ');
	if (end[1] == NULL)
	{
		ft_putendl_fd("", STDOUT_FILENO);	
		return ;
	}
	if (ft_strncmp(end[1], "-n", ft_strlen(end[1])) != 0)
		echo(end, ft_putstr_fd, 1, false);
	else
		echo(end, ft_putstr_fd, 2, true);
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
		if (ft_strncmp(cmd_line, "echo", 4) == 0)
			builtin_echo(cmd_line);
	}
}
