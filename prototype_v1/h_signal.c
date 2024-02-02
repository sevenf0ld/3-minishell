/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:07:02 by folim             #+#    #+#             */
/*   Updated: 2023/11/09 21:07:03 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	char *input;

	input = NULL;
	signal(SIGINT, sighandler);
	while (1)
	{
		input = readline("Enter something: ");
		if (input)
			break ;
	}

	printf("Result: %s\n", input);
	free(input);
	return (0);
}