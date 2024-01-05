/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:36:23 by folim             #+#    #+#             */
/*   Updated: 2023/12/19 16:36:25 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

/*
save the key word after <<
if in the command has that keyword, compare readline with the keyword,
if similar, replace that with new_line
*/

int chck_hdsymbl(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i + 1] == '<' && str[i] == '<')
			return (1);
	}
	return (0);
}

char *hdkywrd(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*kw;

	i = -1;
	while (str[++i])
	{
		if (str[i + 1] == '<' && str[i] == '<')
		{
			i += 1;
			break;
		}
	}
	k = 0;
	j = -1;
	while (str[++i])
	{
		if (str[i] != ' ')
			kw[++j] = str[i];
	}
	kw[++j] = '\0';
	return (kw);
}


int main(int argc, char **argv)
{
	printf("%d\n", chck_hdsymbl(argv[1]));
	// printf("%s\n", hdkywrd(argv[1]));
}
