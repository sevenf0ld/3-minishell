/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_dir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:06:08 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/28 15:23:52 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//getcwd() is not malloced since freeing gives an error
/*
 * mode 'w' for writing
 * mode 's' for storing
 */
char	*b_pwd(t_command *c_node, char mode, t_mini *mi)
{
	char	buf[PATH_MAX];
	char	*cur_dir;

	(void)c_node;
	cur_dir = getcwd(buf, PATH_MAX);
	if (cur_dir != NULL)
	{
		if (mode == 'w')
		{
			ft_putendl_fd(cur_dir, STDOUT_FILENO);
			mi->stat->s_code = 0;
		}
	}
	return (cur_dir);
}

void	mini_err(char *b, char *issue)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(b, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(issue, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(NULL);
}

int	chdir_err(char *path, t_mini *mi)
{
	if (chdir(path) == -1)
	{
		mi->stat->s_code = 1;
		mini_err("cd", path);
		return (1);
	}
	mi->stat->s_code = 0;
	return (0);
}

void	b_cd(t_command *c_node, t_mini *mi)
{
	t_command	*cur;

	cur = c_node;
	if (cur->num_a == 1)
		chdir_err(get_fvalue(c_node->env_var->fixed, "HOME"), mi);
	else
	{
		if (cur->num_a > 2)
		{
			ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
			mi->stat->s_code = 1;
			return ;
		}
		chdir_err(cur->args[1], mi);
	}
}
