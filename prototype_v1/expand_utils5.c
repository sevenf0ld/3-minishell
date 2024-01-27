/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:51:20 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/27 12:44:00 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	contain_exp_norme(char *ref, int *i, int *j, int *q)
{
	if (ref[*i] == 39)
		q[1] *= -1;
	if (ref[*i] == 39
		&& ref[*i + 1]
		&& ref[*i + 1] != ref[*i]
		&& q[0] != 1
		&& q[1] == 1)
	{
		*j = *i + 1;
		while (ref[*j] != ref[*i] && ref[*j])
			(*j)++;
		if (ref[*j] == ref[*i])
		{
			*i = *j;
			q[1] *= -1;
		}
		if (ref[*j] == '\0')
			return (1);
	}
	return (0);
}

// ascii 36 = '$', 39 = single_quote, 34 = double_quote
// q[0] = double_quote, q[1] = single_quote
int	contain_expandable(char *ref)
{
	int	i;
	int	j;
	int	q[2];

	if (ref == NULL)
		return (0);
	i = 0;
	q[0] = -1;
	q[1] = -1;
	while (ref[i] != '\0')
	{
		if (ref[i] == 34)
			q[0] *= -1;
		if (contain_exp_norme(ref, &i, &j, q))
			break ;
		if (ref[i] == 36 && ref[i + 1] && ft_isalnum(ref[i + 1]))
			return (1);
                else if (ref[i] == 36 && ref[i + 1] && ref[i + 1] == 63)
                        return (2);
		if (ref[i] != '\0')
			i++;
	}
	return (0);
}
