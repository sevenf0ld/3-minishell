/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:59 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 13:55:18 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	is_delim(char a, char *delim, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (a == delim[i])
			return (1);
		i++;
	}
	return (0);
}

static int	w_c(char *s, char *delim, size_t n)
{
	int	i;
	int	count;
	int	reset;

	i = 0;
	count = 0;
	reset = 0;
	while (s[i] != '\0')
	{
		if (is_delim(s[i], delim, n))
			count += 1;
		else if (!ft_iswhite(s[i]) && reset == 0 && !is_delim(s[i], delim, n))
		{
			count += 1;
			reset = 1;
		}
		else if (ft_iswhite(s[i]))
			reset = 0;
		i++;
	}
	return (count);
}

static char	*assign_delim(char *s, char a)
{
	s = malloc(sizeof(char) + 1);
	s[0] = a;
	s[1] = '\0';
	return (s);
}

static int	w_l(char *s, char *delim, size_t n)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !ft_iswhite(s[i]) && !is_delim(s[i], delim, n))
		i++;
	return (i);
}

/*
 * breaks the command and arguments into words based on
 * | > < “ ‘ space
 * 124 62 60 34 39 32
 */
char	**new_split(char *str, char *delim, size_t n)
{
	int		i;
	int		j;
	int		count;
	char	**end;

	i = -1;
	j = 0;
	count = w_c(str, delim, n);
	end = malloc(sizeof(char *) * (count + 1));
	while (str[++i] != '\0')
	{
		if (!ft_iswhite(str[i]))
		{
			if (is_delim(str[i], delim, n))
				end[j] = assign_delim(end[j], str[i]);
			else
			{
				end[j] = ft_strndup(str + i, w_l(str + i, delim, n));
				i = i - 1 + w_l(str + i, delim, n);
			}
			j += 1;
		}
	}
	end[j] = NULL;
	return (end);
}
