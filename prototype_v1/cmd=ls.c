/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd=ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2023/11/02 21:22:12 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	cmd_ls(t_command **a)
{
	int			i;
	t_command	*tmp;
	char		**input;
	pid_t		pid;

	tmp = *a;
	if (ft_strcmp(tmp->cmd, "ls"))
		return ;
	input = (char **)malloc_err((tmp->num_f + tmp->num_a + 2) * sizeof(char *));
	input[0] = "/bin/ls";
	input[tmp->num_f + tmp->num_a + 1] = NULL;
	i = 0;
	if (tmp->flags != NULL)
	{
		while (i < tmp->num_f)
		{
			input[i + 1] = tmp->flags[i];
			i++;
		}
	}
	i = 0;
	if (tmp->args != NULL)
	{
		while (i < tmp->num_a)
		{
			input[i + 1] = tmp->args[i];
			i++;
		}
	}
	i = 0;
	if (tmp->args != NULL)
	{
		while (i < tmp->num_a)
		{
			input[i + 1] = tmp->args[i];
			i++;
		}
	}
	pid = fork();
	if (pid == -1)
	{
		free(input);
		return ;
	}
	if (pid == 0)
	{
		if (execve(input[0], input, NULL) == -1)
			perror(">>>ls failed<<<");
	}
	else
	{
		wait(NULL);
		printf(">>>ls success<<<\n");
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
