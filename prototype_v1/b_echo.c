/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:57:44 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/03 11:26:02 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	valid_nl_flag(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	if (!ft_strcmp(s, "-n"))
		return (1);
	if (s[i] == 45)
	{
		while (s[++i] != '\0' && s[i] == 'n')
			;
	}
	if (i == len && len != 0)
		return (1);
	return (0);
}

static void	b_echo_norme(t_command *c_node, int i)
{
	while (c_node->args[i] != NULL)
	{
		if (i + 1 != c_node->num_a)
			printf("%s ", c_node->args[i]);
		else
			printf("%s", c_node->args[i]);
		i++;
	}
}

static int  echo_nl(t_command *c_node)
{
    int i;
    int invalid;

    i = 1;
    invalid = 0;
    while (c_node->args[i] != NULL)
    {
        if (valid_nl_flag(c_node->args[i]) && !invalid)
            return (1);
        invalid += 1;
        i++;
    }
    return (0);
}

void	b_echo(t_command *c_node, t_mini *mi)
{
	int	i;

	i = 0;
	if (c_node->num_a == 1)
	{
		mi->stat->s_code = 0;
		printf("\n");
		return ;
	}
	while (c_node->args[++i] != NULL)
	{
		if (!valid_nl_flag(c_node->args[i]))
			break ;
	}
	b_echo_norme(c_node, i);
        if (!echo_nl(c_node))
            printf("\n");
	mi->stat->s_code = 0;
}
