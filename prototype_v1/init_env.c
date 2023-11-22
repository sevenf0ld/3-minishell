/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 05:49:06 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/23 06:10:32 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*env_new(char *var)
{
	t_env	*node;

	node = malloc_err(sizeof(t_env));
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
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

void	env_init(t_env **envs, char **envp)
{
	t_env	*var;
	int		i;

	var = *ends;
	i = 0;
	while (envp[i] != NULL)
	{
		if (i == 0)
			*envs = env_new(envp[i]);
		else
			env_add_back(envs, env_new(envp[i]));
		i++;
	}
}
