/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:45:36 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 03:24:43 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	b_env(t_command *c_node, t_fixed **f_node, t_mini *mi)
{
	t_fixed	*ftmp;

	ftmp = *f_node;
	if (c_node->num_a > 1)
	{
		mi->stat->s_code = 2;
		ft_putendl_fd("minishell does not require env to handle arguments",
			STDERR_FILENO);
		return ;
	}
	while (ftmp != NULL)
	{
		if (ftmp->fvalue)
			printf("%s=%s\n", ftmp->fkey, ftmp->fvalue);
		ftmp = ftmp->fnext;
	}
	mi->stat->s_code = 0;
}

//static void    b_unset_norme(t_fixed **f_node, char *to_rm)
static void	b_unset_norme(t_fixed *f_node, char *to_rm)
{
	t_fixed	*ftmp;
	t_fixed	*to_free;

	ftmp = f_node;
	if (!ft_strcmp(ftmp->fkey, to_rm))
		*f_node = *ftmp->fnext;
	ftmp = f_node;
	while (ftmp->fnext != NULL)
	{
		if (!ft_strcmp(ftmp->fnext->fkey, to_rm))
		{
			to_free = ftmp->fnext;
			ftmp->fnext = ftmp->fnext->fnext;
			free(to_free->fkey);
			free(to_free->fvalue); //problem 1 & 2 solved
			to_free->fkey = NULL;
			to_free->fvalue = NULL;
			free(to_free);
			to_free = NULL;
			if (!ftmp->fnext)
				break ;
		}
		ftmp = ftmp->fnext;
	}
}

void	b_unset(t_command *c_node, t_fixed **f_node, t_mini *mi)
{
	int	i;

	i = 0;
	(void)f_node;
	if (c_node->num_a == 1)
        {
                mi->stat->s_code = 0;
		return ;
        }
	while (++i < c_node->num_a)
		b_unset_norme(mi->fix, c_node->args[i]);
        mi->stat->s_code = 0;
}
