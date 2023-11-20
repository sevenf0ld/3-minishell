/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:11:26 by folim             #+#    #+#             */
/*   Updated: 2023/11/10 16:09:00 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>

int	main(void)
{
	char *r;

	r = NULL;
	r = readline("");
	if (r == NULL)
		printf("CTRL + C captured\n");
	return (0);
}
