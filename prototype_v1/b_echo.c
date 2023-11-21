/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:57:44 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/22 06:06:58 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	b_echo(t_command	*c_node)
{
	t_command	cur;
	bool		nl;
	int			i;
	int			j;
	int			k;

	cur = *c_node;
	nl = true;
	i = 0;
	k = 1;
	if (cur.num_f > 0)
	{
		while (i < cur.num_f)
		{
			j = 0;
			if (cur.flags[i][0] == 45)
				j += 1;
			while (cur.flags[i][j] != '\0')
			{
				j++;
				if (cur.flags[i][j] == 'n')
					k += 1;
			}
			if (cur.flags[i][k + 1] == '\0')
				nl = false;
			else
			{
				ft_putstr_fd(cur.flags[i], STDOUT_FILENO);
				ft_putchar_fd(' ', STDOUT_FILENO);
			}	
			i++;
		}
	}
	i = -1;
	if (cur.num_a > 0)
	{
		while (++i < cur.num_a)
		{
			ft_putstr_fd(cur.args[i], STDOUT_FILENO);
			if (i < cur.num_a - 1)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
