/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_environ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:45:36 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/25 08:28:05 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	b_env(t_fixed **f_node)
{
	t_fixed	*ftmp;

	ftmp = *f_node;
	while (ftmp != NULL)
	{
		printf("%s=%s\n", ftmp->fkey, ftmp->fvalue);
		ftmp = ftmp->fnext;
	}
}

void	b_unset(t_command *c_node, t_fixed **f_node)
{
	t_fixed	*ftmp;
	t_fixed	*to_free;
	int		i;

	i = -1;
	while (++i < c_node->num_a)
	{
		ftmp = *f_node;
		while (ftmp->fnext != NULL)
		{
			if (!ft_strcmp(ftmp->fnext->fkey, c_node->args[i]))
			{
				to_free = ftmp->fnext;
				ftmp->fnext = ftmp->fnext->fnext;
				free(to_free->fkey);
				to_free->fkey = NULL;
				free(to_free->fvalue);
				to_free->fvalue = NULL;
				free(to_free);
				to_free = NULL;
				if (!ftmp->fnext)
					return;
			}
			ftmp = ftmp->fnext;
		}
	}
}
