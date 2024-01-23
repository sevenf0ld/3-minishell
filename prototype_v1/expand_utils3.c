/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:13:04 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/23 14:31:22 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	is_target(char a)
{
	if (a == '\'' || a == '\"' || a == '$')
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
		if (is_target(s[i]))
			count += 1;
		else if (!ft_iswhite(s[i]) && reset == 0 && !is_target(s[i]))
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

static char	*assign_delim(char *s, char a, t_status *stat)
{
	s = malloc_err(sizeof(char) + 1, stat);
	s[0] = a;
	s[1] = '\0';
	return (s);
}

static int	w_l(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !ft_iswhite(s[i]) && !is_target(s[i]))
		i++;
	return (i);
}

/*
 * breaks the command and arguments into words based on
 * | > < “ ‘ space
 * 124 62 60 34 39 32
 */
char	**new_split(char *str, t_status *stat)
{
	int		i;
	int		j;
	char	**end;

	i = -1;
	j = 0;
	end = malloc(sizeof(char *) * (w_c(str) + 1));
	while (str[++i] != '\0')
	{
		if (!ft_iswhite(str[i]))
		{
			if (is_target(str[i]))
				end[j] = assign_delim(end[j], str[i], stat);
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
