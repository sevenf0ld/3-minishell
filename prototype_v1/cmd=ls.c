/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd=ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2023/11/03 23:24:15 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	cmd_ls(t_command **a)
{
	int			i;
	t_command	*tmp;
	char		**input;
	pid_t		pid;
	char		**path;
	char		*path_str;

	tmp = *a;
	// if (ft_strcmp(tmp->cmd, "ls"))
	// 	return ;
	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		// printf("%s\n", path[i]);
		path_str = ft_strjoin(path[i], "/");
		path_str = ft_strjoin(path_str, tmp->cmd);
		if (!access(path_str, F_OK))
		{
			// printf(">> File '%s' is readable.\n", tmp->cmd); 
			// printf(">> %s\n", path_str);
			break ;
		}
		i++;
	}
	if (!path[i])
		printf("Command not found!\n");

	input = (char **)malloc_err((tmp->num_f + tmp->num_a + 2) * sizeof(char *));
	input[0] = path_str;
	input[tmp->num_f + tmp->num_a + 1] = NULL;
	i = 0;
	if (tmp->flags != NULL)
	{
		while (i < tmp->num_f)
		{
			// printf(">>> %s\n",tmp->flags[i]);
			input[i + 1] = tmp->flags[i];
			i++;
		}
	}
	i = 0;
	if (tmp->args != NULL)
	{
		while (i < tmp->num_a)
		{
			// printf(">>> %s\n",tmp->args[i]);
			input[i + tmp->num_f + 1] = tmp->args[i];
			i++;
		}
	}

	//check **input
	// i = -1;
	// while (input[++i])
	// 	printf("%s, ", input[i]);


	pid = fork();
	if (pid == -1)
	{
		free(input);
		return ;
	}
	if (pid == 0)
	{
		if (execve(input[0], input, NULL) == -1)
			printf("\n>>>%s failed<<<\n", tmp->cmd);
	}
	else
	{
		wait(NULL);
		printf("\n>>>%s success<<<\n", tmp->cmd);
		free(input);
	}
	return ;
}

// stage 1
// run w/o main
// stage 2
// run with optarg
// stage 3
// run with file redirection w/o pipe
// stage 4
// run pipe
// stage 5
// stage 3 and stage 4 mix

// void	cmd_ls_attach(int i)
// {
// 	char	*input[i];

// 		pid = fork();
// 		if (pid == -1)
// 			return ;
// 		if (pid == 0)
// 		{
// 			if (execve(input[0], input, NULL) == -1)
// 			{
// 				perror("execve failed");
// 			}
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			printf("Done execve\n");
// 		}
// 		return ;
// }
