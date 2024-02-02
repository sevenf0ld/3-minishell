/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:43:42 by folim             #+#    #+#             */
/*   Updated: 2024/02/01 16:43:44 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_stat(t_status *status)
{
	if (!status)
		return;
	free(status);
	status = NULL;
}

void	free_res(t_restore *res)
{
	if (!res)
		return;
	free(res);
	res = NULL;
}

void	free_fix(t_fixed **fixed)
{
	t_fixed	*curr;
	t_fixed	*next;

	if (!fixed || !*fixed)
		return;
    curr = *fixed;
    while (curr != NULL)
    {
        next = curr->fnext;
        free(curr->fkey);
		free(curr->fvalue);
        free(curr);
        curr = next;
    }
}

void	free_env(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	if (!env || !*env)
		return;
    curr = *env;
    while (curr != NULL)
    {
        next = curr->next;
        free(curr->key);
		free(curr->value);
        free(curr);
        curr = next;
    }
}
