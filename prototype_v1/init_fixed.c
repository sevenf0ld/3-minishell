/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fixed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 01:59:27 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/24 02:08:33 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_fixed_kv(t_fixed *node, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (var[i] != '\0' && var[i] != '=')
		i++;
	node->fkey = ft_substr(var, 0, i);
	node->fvalue = ft_substr(var, i + 1, len);
}

t_fixed	*f_new(char *var)
{
	t_fixed	*node;

	node = malloc_err(sizeof(t_fixed));
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

void	f_init(t_fixed **envs, char **envp)
{
	t_fixed	*var;
	int		i;

	var = *envs;
	i = 0;
	while (envp[i] != NULL)
	{
		if (i == 0)
			*envs = f_new(envp[i]);
		else
			f_add_back(envs, f_new(envp[i]));
		i++;
	}
}
