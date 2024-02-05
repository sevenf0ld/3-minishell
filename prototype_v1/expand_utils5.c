/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:51:20 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 09:45:47 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	contain_exp_norme_one(char *ref, int *i, int *j, int *q)
{
	if (ref[*i] == 39)
		q[1] *= -1;
	if (ref[*i] == 39 && ref[*i + 1] != '\0' && ref[*i + 1] != ref[*i] && q[0] != 1
		&& q[1] == 1)
	{
		*j = *i + 1;
		while (ref[*j] != '\0' && ref[*j] != ref[*i])
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

static int	contain_exp_norme_two(char *ref, int i)
{
	if (ref[i] == 36 && ref[i + 1] != '\0' && ref[i + 1] == 63)
		return (2);
	else if (ref[i] == 36 && ref[i + 1] != '\0' && !ft_isalnum(ref[i + 1]))
	{
		if (ref[i + 1] == 32 || ref[i + 1] == 34)
			return (0);
		return (3);
	}
	return (-1);
}

int	contain_expandable(char *ref)
{
	int	i;
	int	j;
	int	q[2];

	if (!ref)
		return (0);
	i = 0;
	q[0] = -1;
	q[1] = -1;
	while (ref[i] != '\0')
	{
		if (ref[i] == 34)
			q[0] *= -1;
		if (contain_exp_norme_one(ref, &i, &j, q))
			break ;
		if (ref[i] == 36 && ref[i + 1] != '\0' && ft_isalnum(ref[i + 1]))
			return (1);
		else if (contain_exp_norme_two(ref, i) != -1)
			return (contain_exp_norme_two(ref, i));
		if (ref[i] != '\0')
			i += 1;
	}
	return (0);
}
