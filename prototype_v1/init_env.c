/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 05:49:06 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/24 02:26:57 by maiman-m         ###   ########.fr       */
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

t_env	*env_new(char *var, t_fixed *f)
{
	t_env	*node;

	node = malloc_err(sizeof(t_env));
	set_env_kv(node, var);
	node->fixed = f;
	node->next = NULL;
	/*
	for (t_fixed *tmp = f; tmp != NULL; tmp = tmp->fnext)
		fprintf(stderr, "\x1b[32mFKEY %s FVALUE %s\x1b[m\n", tmp->fkey, tmp->fvalue);
	fprintf(stderr, "--------------------------------------------------------\n");
	for(t_env *tmp = node; tmp != NULL; tmp = tmp->next)
		fprintf(stderr, "\x1b[34m[KEY] %s [VALUE] %s\x1b[m\n", tmp->key, tmp->value);
	*/
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

void	env_init(t_env **envs, char **envp, t_fixed *f)
{
	t_env	*var;
	int		i;

	var = *envs;
	i = 0;
	while (envp[i] != NULL)
	{
		if (i == 0)
			*envs = env_new(envp[i], f);
		else
			env_add_back(envs, env_new(envp[i], f));
		i++;
	}
}
