/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 05:49:06 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/01 12:18:47 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_env_kv(t_env *node, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (var[i] != '\0' && var[i] != '=')
		i++;
	node->key = ft_substr(var, 0, i);
	node->value = ft_substr(var, i + 1, len);
}

t_env	*env_new(char *var, t_fixed *f, t_status *stat)
{
	t_env	*node;

	node = malloc_err(sizeof(t_env), stat);
	set_env_kv(node, var);
	node->fixed = f;
	node->next = NULL;
	return (node);
}

t_env	*env_last(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	env_add_back(t_env **head, t_env *node)
{
	t_env	*old_end;

	if (!node)
		return ;
	old_end = env_last(*head);
	old_end->next = node;
}

void	env_init(t_env **envs, char **envp, t_fixed *f, t_status *stat)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (i == 0)
			*envs = env_new(envp[i], f, stat);
		else
			env_add_back(envs, env_new(envp[i], f, stat));
		i++;
	}
}
