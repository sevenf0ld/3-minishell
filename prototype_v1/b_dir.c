/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_dir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:06:08 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/20 20:39:19 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//getcwd() is not malloced since freeing gives an error
/*
 * mode 'w' for writing
 * mode 's' for storing
 */
char	*b_pwd(t_command *c_node, char mode)
{
	char	buf[PATH_MAX];
	char	*cur_dir;

	cur_dir = getcwd(buf, PATH_MAX);
	if (cur_dir != NULL)
		if (mode == 'w')
		{
			ft_putendl_fd(cur_dir, STDOUT_FILENO);
			c_node->stat->s_code = 0;
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

int chdir_err(char *path, t_command *c_node)
{
    if (path[0] == '~' && path[1] == '/')
    {
        symbols_err(c_node->stat);
        return (1);
    }
    if (chdir(path) == -1)
    {
            c_node->stat->s_code = 1;
            mini_err("cd", path);
            return (1);
    }
    c_node->stat->s_code = 0;
    return (0);
}

void    b_cd_norme(char *path, t_command *c_node)
{
    if (chdir_err(path, c_node))
        return ;
    if (!get_oldpwd(c_node->env_var->fixed))
        f_add_back(&c_node->env_var->fixed, f_new("OLDPWD", c_node->stat));
    update_fvalue(&c_node->env_var->fixed, "OLDPWD", get_fvalue(c_node->env_var->fixed, "PWD"));
    update_fvalue(&c_node->env_var->fixed, "PWD", path);
}

//cd - in bash when first opened shows oldpwd not set
//must reset OLDPWD to be nothing when minishell is first run
void	b_cd(t_command *c_node)
{
	t_command	*cur;
	char		*old;

	cur = c_node;
	old = NULL;
	if (cur->num_a == 1)
	    //chdir_err(get_fvalue("HOME"), cur);
            b_cd_norme(get_fvalue(c_node->env_var->fixed, "HOME"), cur);
	else
	{
            if (cur->num_a > 2)
            {
                ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
                cur->stat->s_code = 1;
                return ;
            }
            if (!ft_strcmp(cur->args[1], "-"))
            {
                old = get_fvalue(c_node->env_var->fixed, "OLDPWD");
                if (!old)
                {
                        ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
                        return ;
                }
                //chdir_err(old, cur);
                b_cd_norme(old, cur);
                b_pwd(cur, 'w');
            }
            else if (!ft_strcmp(cur->args[1], "~"))
	        //chdir_err(get_fvalue("HOME"), cur);
                b_cd_norme(get_fvalue(c_node->env_var->fixed, "HOME"), cur);
            else
                //chdir_err(cur->args[1], cur);
                b_cd_norme(cur->args[1], cur);
    }
}
