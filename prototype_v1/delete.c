/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:31:13 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 07:31:17 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_null(void **content)
{
	if (*content != NULL)
	{
		free(*content);
		*content = NULL;
	}
}

static void	delete_head(t_token **lst, char *value)
{
	t_token	*to_remove;
	
	while (!ft_strcmp((*lst)->token, value))
	{
		to_remove = (*lst);
		*lst = (*lst)->next;
		check_free_and_null(&to_remove->token);
		free_null((void *)&to_remove);
	}

}

static void	delete_free(t_token *to_remove1)
{
	check_free_and_null(&to_remove1->token);
	free_null((void *)&to_remove1);
	return ;

}

void	delete_all_element(t_token **lst, char *value)
{
	t_token	*curr;
	t_token	*to_remove1;

	if (*lst == NULL)
		return ;
	delete_head(lst, value);
	curr = *lst;
	while (curr->next != NULL)
	{
		while (!ft_strcmp(curr->next->token, value))
		{
			to_remove1 = curr->next;
			curr->next = curr->next->next;
			if (curr->next == NULL)
				return (delete_free(to_remove1));
			delete_free(to_remove1);
		}
		curr = curr->next;
	}
}
