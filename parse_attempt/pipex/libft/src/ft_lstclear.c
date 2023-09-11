/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:11:26 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/05 15:39:36 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (!del || !lst)
		return ;
	current = *lst;
	while (*lst != NULL)
	{
		current = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = current;
	}
}
