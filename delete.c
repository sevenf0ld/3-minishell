/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:31:13 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/03 10:37:07 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	delete_head(t_token **lst, char *value)
{
	t_token	*to_remove;

	while (!ft_strcmp((*lst)->token, value))
	{
		to_remove = (*lst);
		*lst = (*lst)->next;
		free(to_remove->token);
		free(to_remove);
	}
}

void	delete_all_element(t_token **lst, char *value)
{
	t_token	*curr;
	t_token	*to_remove1;

	if (*lst == NULL)
		return ;
	curr = *lst;
	while (curr->next != NULL)
	{
		while (!ft_strcmp(curr->next->token, value))
		{
			to_remove1 = curr->next;
			curr->next = curr->next->next;
			if (curr->next == NULL)
			{
				free(to_remove1->token);
				free(to_remove1);
				return ;
			}
			free(to_remove1->token);
			free(to_remove1);
		}
		curr = curr->next;
	}
}
