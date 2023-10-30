/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command=ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2023/10/30 16:02:06 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int	main(void)
{
	char	*argv[] = {"/bin/ls", "-l", NULL};

	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (0);

	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("execve failed");
		}		
	}
	else
	{
		wait(NULL);
		printf("Done execve\n");
	}
	return (0);
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
