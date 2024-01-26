/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:47:11 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 15:54:38 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	set_bfr_exp(char **bfr, char *ref)
{
	int	i;
	int	q[2];

	q[0] = -1;
	q[1] = -1;
	check_free_and_null(bfr);
	i = 0;
	till_dollar(ref, &i, q);
	if (ref[i] == 36)
		*bfr = ft_strndup(ref, i);
}

void	set_aft_exp(char **aft, char *ref)
{
	int	i;
	int	q[2];

	q[0] = -1;
	q[1] = -1;
	check_free_and_null(aft);
	i = 0;
	till_dollar(ref, &i, q);
	if (ref[i] == 36)
	{
		i++;
		while (ft_isalnum(ref[i]) && ref[i])
			i++;
		if (ref[i])
			*aft = ft_substr(ref, i, ft_strlen(ref) - 1);
		else
			*aft = ft_strdup("");
	}
}
