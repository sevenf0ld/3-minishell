/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:52:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 17:11:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	reform_word_norme(char **t, char **u)
{
	char	*tmp;

	tmp = ft_strjoin(*t, *u);
	check_free_and_null(t);
	*t = ft_strdup(tmp);
	check_free_and_null(&tmp);
}

void	check_free_and_null(char **ref)
{
	if (*ref != NULL)
	{
		free(*ref);
		*ref = NULL;
	}
}

void	reform_word(char **s, char **t, char **u, char **v)
{
	char	*tmp;

	tmp = ft_strdup("");
	reform_word_norme(&tmp, t);
	reform_word_norme(&tmp, u);
	reform_word_norme(&tmp, v);
	check_free_and_null(s);
	*s = ft_strdup(tmp);
	check_free_and_null(&tmp);
}

void	till_dollar(char *ref, int *i, int *q)
{
	while (ref[*i])
	{
		if (ref[*i] == 34)
			(q)[0] *= -1;
		if (ref[*i] == 39 && (q)[0] == -1)
			(q)[1] *= -1;
		while ((q)[1] == 1 && ref[*i] && ref[*i + 1] != 39)
			(*i)++;
		if (ref[*i] == 36)
			break ;
		(*i)++;
	}
}
