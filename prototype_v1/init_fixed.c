/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fixed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 01:59:27 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 03:02:41 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_fixed_kv(t_fixed *node, char *var, int flag)
{
	int		i;
	char	*val;

	i = 0;
	val = NULL;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	node->fkey = ft_substr(var, 0, i);
	val = ft_strchr(var, '=');
	if (val != NULL && *val && ft_strlen(val) != 0)
		node->fvalue = ft_strdup(val + 1);
	else
		node->fvalue = NULL;
	if (flag == 1)
		free(var);
}

t_fixed	*f_new(char *var, t_status *stat, int flag)
{
	t_fixed	*node;

	node = malloc_err(sizeof(t_fixed), stat);
	if (node != NULL)
	{
		set_fixed_kv(node, var, flag);
		node->fnext = NULL;
	}
	return (node);
}

t_fixed	*f_last(t_fixed *head)
{
	t_fixed	*tmp;

	tmp = head;
	while (tmp->fnext != NULL)
		tmp = tmp->fnext;
	return (tmp);
}

void	f_add_back(t_fixed **head, t_fixed *node)
{
	t_fixed	*old_end;

	if (!node)
		return ;
	old_end = f_last(*head);
	old_end->fnext = node;
}

void	f_init(t_fixed **envs, char **envp, t_status *stat)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (i == 0)
			*envs = f_new(envp[i], stat, 0);
		else
			f_add_back(envs, f_new(envp[i], stat, 0));
		i++;
	}
}
