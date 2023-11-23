/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_environ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:45:36 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/24 06:53:29 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
void	b_env(t_command *c_node)
{
	t_env	*var;

	var = c_node->env_var;
	while (var != NULL)
	{
		if (!ft_strcmp(getenv(var->key), "(null)"))
			continue ;
		printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
}
*/

void	b_env(t_fixed **f_node)
{
	printf("\x1b[34mIN ENV, f_node is @ %p\x1b[m\n", f_node);
	t_fixed	*ftmp;

	ftmp = *f_node;
	while (ftmp != NULL)
	{
		/*
		if (ftmp->fvalue != NULL)
			printf("%s=%s\n", ftmp->fkey, ftmp->fvalue);
		else
			printf("THIS WAS REMOVED %s=%s\n", ftmp->fkey, ftmp->fvalue);
		*/
		printf(":::%s:::%s\n", ftmp->fkey, ftmp->fvalue);
		ftmp = ftmp->fnext;
	}
}

void	b_unset(t_command *c_node, t_fixed **f_node)
{
	printf("\x1b[31mIN UNSET, f_node is @ %p\x1b[m\n", f_node);
	t_fixed	*ftmp;
	t_fixed	*to_free;

	ftmp = *f_node;
	to_free = NULL;
	while (ftmp->fnext != NULL)
	{
		if (!ft_strcmp(ftmp->fnext->fkey, c_node->args[0]))
		{
			free(ftmp->fnext->fkey);
			ftmp->fnext->fkey = NULL;
			free(ftmp->fnext->fvalue);
			ftmp->fnext->fvalue = NULL;
			to_free = ftmp->fnext;
			if (ftmp->fnext->fnext != NULL)
				ftmp->fnext = ftmp->fnext->fnext;
			else
				ftmp->fnext = NULL;
			free(to_free);
			to_free = NULL;
		}
		else
			ftmp = ftmp->fnext;
	}
	/*
	while (ftmp != NULL)
	{
		if (!ft_strcmp(ftmp->fkey, c_node->args[0]))
		{
			to_free = ftmp;
			ftmp = ftmp->fnext;
			free(to_free->fkey);
			to_free->fkey = NULL;
			free(to_free->fvalue);
			to_free->fvalue = NULL;
			free(to_free);
			continue ;
		}
		else
			ftmp = ftmp->fnext;
	}
	*/
}
