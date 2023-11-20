/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:49:45 by folim             #+#    #+#             */
/*   Updated: 2023/11/10 23:26:01 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int sig = 0;


char	*siganl_cntrl_c(char *pipeline);
void	sighandler_c(int signum);



void	sighandler_c(int signum)
{
	sig = 1;
	printf("\n%d\n", sig);
}

char	*siganl_cntrl_c(char *pipeline)
{
	pipeline = NULL;
	printf(">1\n");
	printf(">2\n");
	signal(SIGINT, sighandler_c);
	while (!pipeline)
	{
		if (sig == 1)
		{
			sig = 0;
			printf("in loop\n");
			pipeline = siganl_cntrl_c(pipeline);
			return pipeline;
		}
		pipeline = readline("prompt> ");
	}
	return pipeline;
}

int	main(void)
{
	char	*pipeline;

	pipeline = NULL;
	pipeline = siganl_cntrl_c(pipeline);
	printf("pipeline = %s$\n", pipeline);
	// printf("Control + C is hit\n");
	return (0);
}
