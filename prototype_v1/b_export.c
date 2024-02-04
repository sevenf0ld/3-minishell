/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:29:27 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 02:43:44 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

static t_fixed	*export_repl(t_fixed *ftmp, t_fixed *to_repl, char *to_ref)
{
	char	*val;
	char	*key;

	val = ft_strchr(to_ref, '=');
	key = get_key(to_ref);
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
		check_free_and_null(&to_repl->fkey);
		to_repl->fkey = key;
		if (val != NULL && *val)
		{
			check_free_and_null(&to_repl->fvalue);
			to_repl->fvalue = ft_strdup(val + 1);
		}
	}
	else
		check_free_and_null(&key);
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
		{
			if (*ftmp->fvalue)
				printf("%s=\"%s\"\n", ftmp->fkey, ftmp->fvalue);
			else
				printf("%s=\"\"\n", ftmp->fkey);
		}
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
		return (export_argless(mi, f_node));
	while (++i < c_node->num_a)
	{
		ftmp = *f_node;
		to_repl = NULL;
		if (!valid_identifier(c_node->args[i]))
			return (export_err(c_node->args[i], mi));
		to_repl = export_repl(ftmp, to_repl, c_node->args[i]);
		if (!to_repl)
			f_add_back(f_node, f_new(
					ft_strdup(c_node->args[i]), c_node->stat, 1));
	}
	mi->stat->s_code = 0;
}
