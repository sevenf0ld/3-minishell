/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:57:44 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 19:37:31 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	b_echo(t_command	*c_node)
{
	t_command	cur;
	int		i;

	cur = *c_node;
	i = 0;

        if (cur.num_a == 1)
        {
            printf("\n");
            return ;
        }
        while (cur.args[++i] != NULL)
        {
            if (i == 1 && !ft_strcmp(cur.args[i], "-n"))
                continue ;
            if (i + 1 != cur.num_a)
                printf("%s ", cur.args[i]);
            else
                printf("%s", cur.args[i]);
        }
        if (i >= 2 && ft_strcmp(cur.args[1], "-n") != 0)
            printf("\n");
}
