/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:43:42 by folim             #+#    #+#             */
/*   Updated: 2024/02/05 09:02:04 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_stat(t_status *status)
{
	if (!status)
		return ;
	free_null((void *)&status);
}

void	free_res(t_restore *res)
{
	if (!res)
		return ;
	free_null((void *)&res);
}

void	free_fix(t_fixed **fixed)
{
	t_fixed	*curr;
	t_fixed	*next;

	if (!fixed || !*fixed)
		return ;
	curr = *fixed;
	while (curr != NULL)
	{
		next = curr->fnext;
		check_free_and_null(&curr->fkey);
		check_free_and_null(&curr->fvalue);
		free_null((void *)&curr);
		curr = next;
	}
}

void	free_env(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	if (!env || !*env)
		return ;
	curr = *env;
	while (curr != NULL)
	{
		next = curr->next;
		check_free_and_null(&curr->key);
		check_free_and_null(&curr->value);
		free_null((void *)&curr);
		curr = next;
	}
}

void	free_mini(t_mini *mi)
{
	free_stat(mi->stat);
	free_res(mi->res);
	free_fix(&mi->fix);
	free_env(&mi->env);
}
