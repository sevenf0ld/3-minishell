/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2024/02/05 00:02:34 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
   return 1 if absolute path
   return 0 if relative path
   return -1 on error
   return 2 if ./
*/
//n_builtins_3
static int	check_path_type(char *path_str)
{
	if (path_str[0] == '.' && path_str[1] == '/')
		return (2);
	else if (!access(path_str, F_OK))
		return (1);
	else if (path_str[0] == '/')
		return (-1);
	return (0);
}

//n_builtins
static char	*get_path_str(char *path, char *cmd)
{
	char	**env_path;
	char	*path_str;
	int		i;

	env_path = ft_split(path, ':');
	path_str = NULL;
	i = 0;
	while (env_path[i] != NULL)
	{
		path_str = ft_strjoin(env_path[i], "/");
		path_str = join_and_free(path_str, cmd);
		if (!access(path_str, F_OK))
		{
			free_2d_arr(env_path);
			return (path_str);
		}
		free(path_str);
		path_str = NULL;
		i++;
	}
	free_2d_arr(env_path);
	return (NULL);
}

static void	execute_non_exe(t_command *c_node, t_mini *mi)
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
static int	execute_b_nb(t_command *c_node, t_mini *mi, char *path_str)
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
		{
			free_2d_arr(envp);
			return (path_err(c_node, 1, mi->stat));
		}
		path_str = get_path_str(path, c_node->cmd);
		if (!path_str || !ft_strlen(c_node->cmd))
		{
			free_2d_arr(envp);
			return (path_err(c_node, 2, mi->stat));
		}
		free(c_node->args[0]);
		c_node->args[0] = ft_strdup(path_str);
		free(path_str);
		path_str = NULL;
	}
	return (mini_exec(c_node, mi, envp));
}

//n_builtins
void	fork_exec(t_command *c_node, t_mini *mi)
{
	int		abs_rel_path;
	char	*path_str;

	if (!c_node->cmd && c_node->exec)
		mi->stat->s_code = 0;
	update_cmd_exec(c_node);
	if (!c_node->exec)
		return ;
	c_node->cmd = c_node->args[0];
	if (!ft_strlen(c_node->cmd))
	{
		mi->stat->s_code = 0;
		return ;
	}
	abs_rel_path = check_path_type(c_node->cmd);
	path_str = NULL;
	if (abs_rel_path == -1)
		path_err(c_node, 1, mi->stat);
	else if (abs_rel_path == 2)
		execute_non_exe(c_node, mi);
	else if (abs_rel_path == 1 || abs_rel_path == 0)
	{
		if (abs_rel_path == 1)
			path_str = c_node->cmd;
		execute_b_nb(c_node, mi, path_str);
	}
}
