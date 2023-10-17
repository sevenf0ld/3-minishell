/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2023/10/17 14:17:09 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mini.h"

void	expansion(t_token **lst)
{
	t_token	*curr;
	int		check[2];

	if (*lst == NULL)
		return ;
	curr = *lst;
	curr = curr->next;
	while (curr != NULL)
	{
		check[0] = 0;
		check[1] = 0;
		if (!ft_strcmp(curr->prev->token, "\'"))
			check[0] = 1;
		if (ft_strchr(curr->token, '$'))
			check[1] = 1;
		if (check[0] == 0 && check[1] == 1)
			curr->exp = true;
		curr = curr->next;
	}
}
