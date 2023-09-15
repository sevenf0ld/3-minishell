/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:59 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 15:56:55 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	is_delim(char a)
{
	if (mini_delim(a))
		return (1);
	return (0);
}

static int	w_c(char *s)
{
	int	i;
	int	count;
	int	reset;

	i = 0;
	count = 0;
	reset = 0;
	while (s[i] != '\0')
	{
		if (is_delim(s[i]))
			count += 1;
		else if (!ft_iswhite(s[i]) && reset == 0 && !is_delim(s[i]))
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

static int	w_l(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !ft_iswhite(s[i]) && !is_delim(s[i]))
		i++;
	return (i);
}

/*
 * breaks the command and arguments into words based on
 * | > < “ ‘ space ( ) &
 * 124 62 60 34 39 32 40 41 38
 */
char	**new_split(char *str)
{
	int		i;
	int		j;
	int		count;
	char	**end;

	i = -1;
	j = 0;
	count = w_c(str);
	end = malloc(sizeof(char *) * (count + 1));
	while (str[++i] != '\0')
	{
		if (!ft_iswhite(str[i]))
		{
			if (is_delim(str[i]))
				end[j] = assign_delim(end[j], str[i]);
			else
			{
				end[j] = ft_strndup(str + i, w_l(str + i));
				i = i - 1 + w_l(str + i);
			}
			j += 1;
		}
	}
	end[j] = NULL;
	return (end);
}
