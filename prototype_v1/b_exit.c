/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:42:44 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/25 12:45:22 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	b_exit(t_command *c_node)
{
	//if (!ft_strcmp(c_node->cmd, "exit"))
		//exit(EXIT_SUCCESS);
	if (c_node->num_a == 0)
		exit(c_node->stat->s_code);
	else
	{
		//for (int i = 0; i < c_node->num_a; i++)
			//printf("arg %i is %s\n", i + 1, c_node->args[i]);
		c_node->stat->s_code = ft_atoi(c_node->args[0]);
		exit(c_node->stat->s_code);
	}
}
