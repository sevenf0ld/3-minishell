/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:57:44 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/28 15:20:57 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int  valid_nl_flag(char *s)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(s);
    if (!ft_strcmp(s, "-n"))
        return (1);
    if (s[i] == 45)
    {
        while (s[++i] != '\0' && s[i] == 'n')
            ;
    }
    if (i == len)
        return (1);
    return (0);
}

static void b_echo_norme(t_command *c_node, int i, int j)
{
    while (c_node->args[i] != NULL)
    {
        if (i + 1 != c_node->num_a)
            printf("%s ", c_node->args[i]);
        else
            printf("%s", c_node->args[i]);
        i++;
    }
    if (j == 1)
        printf("\n");
}

void	b_echo(t_command *c_node, t_mini *mi)
{
	int		i;
        int             j;

	i = 0;
        j = 1;

        if (c_node->num_a == 1)
        {
            printf("\n");
            return ;
        }
        while (c_node->args[++i] != NULL)
        {
            if (!valid_nl_flag(c_node->args[i]))
            {
                j = i;
                break ;
            }
        }
        b_echo_norme(c_node, i, j);
        mi->stat->s_code = 0;
}
