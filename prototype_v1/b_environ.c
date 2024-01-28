/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_environ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:45:36 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/28 15:24:46 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	b_env(t_command *c_node, t_fixed **f_node, t_mini *mi)
{
	t_fixed	*ftmp;

	ftmp = *f_node;
	if (c_node->num_a > 1)
	{
            mi->stat->s_code = 64;
            ft_putendl_fd("minishell does not require env to handle arguments", STDERR_FILENO);
	    return ;
	}
	while (ftmp != NULL)
	{
		if (ftmp->fvalue)
			printf("%s=%s\n", ftmp->fkey, ftmp->fvalue);
		ftmp = ftmp->fnext;
	}
	mi->stat->s_code = 0;
}

void	b_unset(t_command *c_node, t_fixed **f_node, t_mini *mi)
{
	t_fixed	*ftmp;
	t_fixed	*to_free;
	int		i;
	int		len;

	i = -1;
	if (c_node->num_a == 0)
		return ;
	while (++i < c_node->num_a)
	{
		ftmp = *f_node;
		while (ftmp->fnext != NULL)
		{
			if (!ft_strcmp(ftmp->fnext->fkey, c_node->args[i]))
			{
				to_free = ftmp->fnext;
				ftmp->fnext = ftmp->fnext->fnext;
				free(to_free->fkey);
				to_free->fkey = NULL;
				free(to_free);
				to_free = NULL;
				if (!ftmp->fnext)
					break ;
			}
			ftmp = ftmp->fnext;
		}
		len = ft_strlen(c_node->args[i]);
		if (!ft_isalnum(c_node->args[i][len - 1]) && c_node->args[i][len] == '\0')
		{
			mi->stat->s_code = 1;
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(c_node->args[0], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return ;
		}
	}
}

static char	*get_key(char *exported)
{
	int	i;

	i = 0;
	while (exported[i] != '\0' && exported[i] != '=')
		i++;
	return (ft_substr(exported, 0, i));
}

void	b_export(t_command *c_node, t_fixed **f_node, t_mini *mi)
{
	t_fixed	*ftmp;
	t_fixed	*to_repl;
	int		i;
	char	*val;
	char	*key;

	i = 0;
	if (c_node->num_a == 1)
	{
		ftmp = *f_node;
		while (ftmp != NULL)
		{
			printf("declare -x ");
			if (!ftmp->fvalue)
				printf("%s\n", ftmp->fkey);
			else
				printf("%s=\"%s\"\n", ftmp->fkey, ftmp->fvalue);
			ftmp = ftmp->fnext;
		}
		mi->stat->s_code = 0;
		return ;
	}
	while (++i < c_node->num_a)
	{
		ftmp = *f_node;
		to_repl = NULL;
		val = ft_strchr(c_node->args[i], '=');
		key = get_key(c_node->args[i]);
		while (ftmp != NULL)
		{
			if (!ft_strcmp(ftmp->fkey, key))
			{
				to_repl = ftmp;
				break ;
			}
			ftmp = ftmp->fnext;
		}
		if (to_repl != NULL)
		{
			to_repl->fkey = key;
			if (val != NULL)
				to_repl->fvalue = val + 1;
		}
		else
			f_add_back(f_node, f_new(c_node->args[i], c_node->stat));
	}
	mi->stat->s_code = 0;
}
