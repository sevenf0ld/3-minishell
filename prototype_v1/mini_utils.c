/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:50 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 17:43:44 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	save_io(t_mini *mi)
{
	t_restore	*res;
	t_status	*stat;

	res = mi->res;
	stat = mi->stat;
	res->std_out = dup_err(STDOUT_FILENO, stat);
	res->std_in = dup_err(STDIN_FILENO, stat);
}

void	no_fork_b_exec(t_mini *mi, t_command *cur)
{
	t_fixed	*fix;

	fix = mi->fix;
	if (!cur->cmd || !cur->builtin)
		return ;
	if (!ft_strcmp(cur->cmd, "unset") && cur->size == 1)
		b_unset(cur, &fix, mi);
	if (!ft_strcmp(cur->cmd, "exit") && cur->size == 1)
		b_exit(cur, mi);
	if (!ft_strcmp(cur->cmd, "export") && cur->size == 1)
		b_export(cur, &fix, mi);
	if (!ft_strcmp(cur->cmd, "cd") && cur->size == 1)
		b_cd(cur, mi);
}

void	restore_io(t_mini *mi)
{
	t_restore	*res;
	t_status	*stat;

	res = mi->res;
	stat = mi->stat;
	dup2_err(res->std_out, STDOUT_FILENO, stat);
	dup2_err(res->std_in, STDIN_FILENO, stat);
}
