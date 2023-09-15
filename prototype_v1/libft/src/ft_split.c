/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:36:50 by maiman-m          #+#    #+#             */
/*   Updated: 2023/06/07 16:07:49 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	validate(char a, char c)
{
	if (a == '\0')
		return (1);
	if (c == a)
		return (1);
	return (0);
}

static int	word_counter(const char *s, char c)
{
	int	i;
	int	counter;
	int	reset;

	i = 0;
	counter = 0;
	reset = 0;
	while (s[i] != '\0')
	{
		if (!(validate(s[i], c)) && reset == 0)
		{
			counter++;
			reset++;
		}
		if (validate(s[i], c))
			reset = 0;
		i++;
	}
	return (counter + 1);
}

static int	word_length(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
	{
		if (validate(s[len], c))
			return (len);
		len++;
	}
	return (len);
}

static void	write_into(char *t, const char *s, char c)
{
	int	i;

	i = 0;
	while (!validate(s[i], c))
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**end;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	end = malloc(word_counter(s, c) * sizeof(char *));
	if (!end)
		return (NULL);
	while (s[i] != '\0')
	{
		if (!(validate(s[i], c)))
		{
			end[j] = malloc(word_length((char *)s + i, c) + 1);
			write_into(end[j], s + i, c);
			i = i + word_length(s + i, c);
			j++;
			continue ;
		}
		i++;
	}
	end[j] = NULL;
	return (end);
}
