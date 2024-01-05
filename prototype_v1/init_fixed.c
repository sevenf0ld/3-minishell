/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fixed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 01:59:27 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/30 12:47:36 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_fixed_kv(t_fixed *node, char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	node->fkey = ft_substr(var, 0, i);
	node->fvalue = ft_strchr(var, '=');
	if (node->fvalue != NULL)
		node->fvalue += 1;
}

t_fixed	*f_new(char *var, t_status *stat)
{
	t_fixed	*node;

	node = malloc_err(sizeof(t_fixed), stat);
	set_fixed_kv(node, var);
	node->fnext = NULL;
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
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (i == 0)
			*envs = f_new(envp[i], stat);
		else
			f_add_back(envs, f_new(envp[i], stat));
		i++;
	}
}
