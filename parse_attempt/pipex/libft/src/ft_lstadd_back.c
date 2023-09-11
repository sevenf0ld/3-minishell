/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:24:29 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/05 15:04:02 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;
	t_list	*last;

	current = *lst;
	if (!new || !(lst))
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
}
