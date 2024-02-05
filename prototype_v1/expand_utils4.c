/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:52:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 09:43:27 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	check_free_and_null(char **ref)
{
	if (*ref != NULL)
	{
		free(*ref);
		*ref = NULL;
	}
}

static void	reform_word_norme(char **old, char **new)
{
	char	*tmp;

	tmp = ft_strjoin(*old, *new);
	check_free_and_null(old);
	*old = ft_strdup(tmp);
	check_free_and_null(&tmp);
}

void	reform_word(char **tokens, char **bfr, char **sub, char **aft)
{
	char	*tmp;

	tmp = ft_strdup("");
	reform_word_norme(&tmp, bfr);
	reform_word_norme(&tmp, sub);
	reform_word_norme(&tmp, aft);
	check_free_and_null(tokens);
	*tokens = ft_strdup(tmp);
	check_free_and_null(&tmp);
}

void	till_dollar(char *ref, int *i, int *q)
{
	while (ref[*i] != '\0')
	{
		if (ref[*i] == 34)
			q[0] *= -1;
		if (ref[*i] == 39 && q[0] == -1)
			q[1] *= -1;
		while (q[1] == 1 && ref[*i] != '\0' && ref[*i + 1] != 39)
			(*i)++;
		if (ref[*i] != '\0' && ref[*i] == 36)
			break ;
		(*i)++;
	}
}
