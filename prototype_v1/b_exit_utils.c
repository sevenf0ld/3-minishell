/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:19:14 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 12:20:57 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	conditional_exit_display(int size)
{
	if (size == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
}

int	exit_err(t_mini *mi, int flag, t_command *c_node)
{
	if (flag == 2)
	{
		conditional_exit_display(c_node->size);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(c_node->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		mi->stat->s_code = 2;
		garbage_burner(mi);
		exit(mi->stat->s_code);
		return (1);
	}
	else if (flag == 1)
	{
		if (c_node->num_a > 2)
		{
			conditional_exit_display(c_node->size);
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			mi->stat->s_code = 1;
			return (1);
		}
	}
	return (0);
}
