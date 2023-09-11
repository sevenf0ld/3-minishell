/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:17:57 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/05 15:33:54 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*n_list;
	t_list	*n_node;

	n_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	while (current != NULL)
	{
		n_node = ft_lstnew(f(current->content));
		if (!n_node)
		{
			ft_lstclear(&n_list, del);
			n_list = NULL;
			return (n_list);
		}
		ft_lstadd_back(&n_list, n_node);
		current = current->next;
	}
	return (n_list);
}
