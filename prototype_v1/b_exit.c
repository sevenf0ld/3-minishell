/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:42:44 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/20 10:50:38 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	b_exit(t_command *c_node)
{
	long long	conv;

	if (c_node->num_a == 1)
	{
		conv = ft_atoll(c_node->args[0]);
		if (!ft_strcmp(ft_lltoa(conv), c_node->args[0]))
		{
			if (conv > 255)
				c_node->stat->s_code = conv % 256;
			else
				c_node->stat->s_code = conv;
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", c_node->args[0]);
			c_node->stat->s_code = 255;
		}
	}
	else if (c_node->num_a > 1)
	{
		printf("minishell: exit: too many arguments\n");
		c_node->stat->s_code = 1;
		return ;
	}
	exit(c_node->stat->s_code);
}
