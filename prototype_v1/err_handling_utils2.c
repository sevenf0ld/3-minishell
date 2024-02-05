/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:15 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 08:58:26 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	symbols_err(t_status *stat)
{
	report_err("minishell: this is not required by the subject\n", 0, stat);
	return (1);
}

int	pipe_related_err(t_status *stat)
{
	report_err("minishell: syntax error near unexpected token `|'\n", 0, stat);
	return (1);
}

int	path_err(t_command *c_node, int flag, t_status *stat, char **envp)
{
	c_node->exec = false;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(c_node->cmd, STDERR_FILENO);
	if (flag == 1)
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
	else if (flag == 2)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	stat->s_code = 127;
	free_2d_arr(envp);
	return (1);
}

void	export_err(char *err_arg, t_mini *mi)
{
	mi->stat->s_code = 1;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(err_arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return ;
}
