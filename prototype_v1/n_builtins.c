/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2024/02/05 12:40:22 by maiman-m         ###   ########.fr       */
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
char	*get_path_str(char *path, char *cmd)
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

static int	stop_exec(t_command *c_node, t_mini *mi)
{
	if (!c_node->cmd && c_node->exec)
		mi->stat->s_code = 0;
	update_cmd_exec(c_node);
	if (!c_node->exec)
		return (1);
	c_node->cmd = c_node->args[0];
	if (!ft_strlen(c_node->cmd))
	{
		mi->stat->s_code = 0;
		return (1);
	}
	return (0);
}

//n_builtins
void	fork_exec(t_command *c_node, t_mini *mi)
{
	int		abs_rel_path;
	char	*path_str;

	if (stop_exec(c_node, mi))
		return ;
	abs_rel_path = check_path_type(c_node->cmd);
	path_str = NULL;
	if (abs_rel_path == -1)
		path_err(c_node, 1, mi->stat, NULL);
	else if (abs_rel_path == 2)
		execute_non_exe(c_node, mi);
	else if (abs_rel_path == 1 || abs_rel_path == 0)
	{
		if (abs_rel_path == 1)
			path_str = c_node->cmd;
		execute_b_nb(c_node, mi, path_str);
	}
}
