/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_dir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:06:08 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/23 05:04:14 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//getcwd() is not malloced since freeing gives an error
/*
 * mode 'w' for writing
 * mode 's' for storing
 */
char	*b_pwd(char mode)
{
	char	buf[PATH_MAX];
	char	*cur_dir;

	cur_dir = getcwd(buf, PATH_MAX);
	if (cur_dir != NULL)
		if (mode == 'w')
			ft_putendl_fd(cur_dir, STDOUT_FILENO);
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

void	chdir_err(char	*path)
{
	if (chdir(path) == -1)
		mini_err("cd", path);
}

//cd - in bash when first opened shows oldpwd not set
//must reset OLDPWD to be nothing when minishell is first run
void	b_cd(t_command *c_node)
{
	t_command	*cur;
	char		*old;

	cur = c_node;
	old = NULL;
	if (!cur->args)
		chdir_err(getenv("HOME"));
	else
	{
		if (!ft_strcmp(cur->args[0], "-"))
		{
			old = getenv("OLDPWD");
			if (!old)
			{
				ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
				return ;
			}
			chdir_err(old);
			b_pwd('w');
		}
		else if (!ft_strcmp(cur->args[0], "~"))
			chdir_err(getenv("HOME"));
		else
			chdir_err(cur->args[0]);
	}
}
