/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_environ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:45:36 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/31 12:37:49 by maiman-m         ###   ########.fr       */
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
		ft_putendl_fd("minishell does not require env to handle arguments",
			STDERR_FILENO);
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

//static void    b_unset_norme(t_fixed **f_node, char *to_rm)
static void	b_unset_norme(t_fixed *f_node, char *to_rm)
{
	t_fixed	*ftmp;
	t_fixed	*to_free;

	ftmp = f_node;
	if (!ft_strcmp(ftmp->fkey, to_rm))
		*f_node = *ftmp->fnext;
	ftmp = f_node;
	while (ftmp->fnext != NULL)
	{
		if (!ft_strcmp(ftmp->fnext->fkey, to_rm))
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
}

void	b_unset(t_command *c_node, t_fixed **f_node, t_mini *mi)
{
	int	i;

	i = 0;
	(void)f_node;
	if (c_node->num_a == 1)
		return ;
	while (++i < c_node->num_a)
		b_unset_norme(mi->fix, c_node->args[i]);
}

static char	*get_key(char *exported)
{
	int	i;

	i = 0;
	while (exported[i] != '\0' && exported[i] != '=')
		i++;
	return (ft_substr(exported, 0, i));
}

static int	valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '\0' && !ft_isalpha(s[i]))
		return (0);
	i += 1;
	while (s[i] != '\0' && ft_isalpha(s[i]))
		i++;
	while (s[i] != '\0' && ft_isalnum(s[i]))
		i++;
	if (s[i] != '\0' && !ft_isalnum(s[i]) && s[i] != 61)
		return (0);
	return (1);
}

static void	export_err(char *err_arg, t_mini *mi)
{
	mi->stat->s_code = 1;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(err_arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return ;

}

static t_fixed	*export_repl(t_fixed *ftmp, t_fixed	*to_repl, char *to_ref
{
	char	*val;
	char	*key;

	
	val = ft_strchr(to_ref, '=');
	key = get_key(to_ref);
	while (f_node != NULL)
	{
		if (!ft_strcmp(f_node->fkey, key))
		{
			to_repl = f_node;
			break ;
		}
		f_node = f_node->fnext;
	}
	if (to_repl != NULL)
	{
		to_repl->fkey = key;
		if (val != NULL)
			to_repl->fvalue = val + 1;
	}
	return (to_repl);
}

static void	export_argless(t_mini *mi, t_fixed **f_node)
{
	t_fixed	*ftmp;

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

void	b_export(t_command *c_node, t_fixed **f_node, t_mini *mi)
{
	t_fixed	*ftmp;
	t_fixed	*to_repl;
	int		i;

	i = 0;
	if (c_node->num_a == 1)
		return (export_argless(ftmp, mi));
	while (++i < c_node->num_a)
	{
		ftmp = *f_node;
		to_repl = NULL;
		if (!valid_identifier(c_node->args[i]))
			return (export_err(c_node->args[i], mi));
		to_repl = export_repl(ftmp, to_repl, c__node->args[i]);
		if (!to_repl)
			f_add_back(f_node, f_new(c_node->args[i], c_node->stat));
	}
	mi->stat->s_code = 0;
}
