/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_ll_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:10:50 by folim             #+#    #+#             */
/*   Updated: 2023/11/15 15:53:00 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*double_ll_convert(t_token **lst)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*tail;

	if (*lst == NULL)
		return (NULL);
	prev = NULL;
	curr = *lst;
	while (curr != NULL)
	{
		curr->prev = prev;
		prev = curr;
		curr = curr->next;
	}
	tail = prev;
	return (tail);
}

t_command	*double_ll_convert2(t_command **lst)
{
	t_command	*prev;
	t_command	*curr;
	t_command	*tail;

	if (*lst == NULL)
		return (NULL);
	prev = NULL;
	curr = *lst;
	while (curr != NULL)
	{
		curr->prev = prev;
		prev = curr;
		curr = curr->next;
	}
	tail = prev;
	return (tail);
}

t_pipe	*double_ll_convert3(t_pipe **lst)
{
	t_pipe	*prev;
	t_pipe	*curr;
	t_pipe	*tail;

	if (*lst == NULL)
		return (NULL);
	prev = NULL;
	curr = *lst;
	while (curr != NULL)
	{
		curr->prev = prev;
		prev = curr;
		curr = curr->next;
	}
	tail = prev;
	return (tail);
}
// typedef struct s_token
// {
// 	int				x;
// 	char			*str;
// 	struct s_token	*prev;
// 	struct s_token	*next;
// }t_token;
// double_ll_convert takes in the root of the linked list and returns
// the tail of the linked list.
