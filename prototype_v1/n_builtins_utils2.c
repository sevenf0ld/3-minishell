/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:49:45 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 10:18:21 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	execute_non_exe(t_command *c_node, t_mini *mi)
{
	if (access(c_node->cmd + 2, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		report_err(c_node->cmd, 1, mi->stat);
		mi->stat->s_code = 127;
	}
	else if (access(c_node->cmd + 2, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		report_err(c_node->cmd, 1, mi->stat);
		mi->stat->s_code = 126;
	}
	else
		ft_putendl_fd("not required by the subject", STDERR_FILENO);
}

//n_builtins & n_builtins_1
int	execute_b_nb(t_command *c_node, t_mini *mi, char *path_str)
{
	char	*path;
	char	**envp;

	path = NULL;
	envp = malloc_err(sizeof(char *) * 2, mi->stat);
	envp[0] = ft_strjoin("TERM=", get_fvalue(mi->fix, "TERM"));
	envp[1] = NULL;
	if (c_node->builtin)
		return (mini_exec(c_node, mi, envp));
	if (!path_str)
	{
		path = get_fvalue(mi->fix, "PATH");
		if (!path)
			return (path_err(c_node, 1, mi->stat, NULL));
		path_str = get_path_str(path, c_node->cmd);
		if (!path_str || !ft_strlen(c_node->cmd))
			return (path_err(c_node, 2, mi->stat, NULL));
		check_free_and_null(&c_node->args[0]);
		c_node->args[0] = ft_strdup(path_str);
		check_free_and_null(&path_str);
	}
	return (mini_exec(c_node, mi, envp));
}
