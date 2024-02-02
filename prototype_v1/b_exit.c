/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:33:37 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 11:33:39 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	rm_plus_sign(char **s)
{
	char	*tmp;
	int		i;

	tmp = *s;
	i = 0;
	while (tmp[i] != '\0' && tmp[i] == 43)
		i++;
	if (i == 1)
		*s = tmp + 1;
}

static void	exit_err(t_mini *mi, int flag, t_command *c_node)
{
	if (flag == 2)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(c_node->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		mi->stat->s_code = 2;
		exit(mi->stat->s_code);
	}
	else if (flag == 1)
	{
		if (c_node->num_a > 2)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			mi->stat->s_code = 1;
			return ;
		}
	}
}

static void	exit_calc(long long code, t_mini *mi)
{
	if (code >= 0)
	{
		if (code > 255)
			mi->stat->s_code = code % 256;
		else
			mi->stat->s_code = code;
	}
	else
	{
		mi->stat->s_code = code + 256;
		if (code <= -255)
			mi->stat->s_code %= (256 + 0U);
	}
}

void	b_exit(t_command *c_node, t_mini *mi)
{
	long long	code;

	if (c_node->num_a == 1)
	{
		mi->stat->s_code = 0;
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(mi->stat->s_code);
		return ;
	}
	code = ft_atoll(c_node->args[1]);
	rm_plus_sign(&c_node->args[1]);
	if (ft_strcmp(ft_lltoa(code), c_node->args[1]) != 0)
		return (exit_err(mi, 2, c_node));
	else
		return (exit_err(mi, 1, c_node));
	exit_calc(code, mi);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(mi->stat->s_code);
}
