/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:36:05 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/16 17:32:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	manage_quotes(t_token **tokens)
{
	t_token	*tmp;
	int		num;

	tmp = *tokens;
	num = 0;
	while (tmp != NULL) 
	{
		if (!ft_strcmp(tmp->token, "\"") || !ft_strcmp(tmp->token, "'"))
		{
			num += 1;
			if (num == 2)
			{
				if (tmp->next != NULL)
					if (!is_delim(tmp->next->token[0]))
						tmp->next->rm = true;
				num = 0;
			}
		}
		printf("%s and %i\n", tmp->token, tmp->rm);
		tmp = tmp->next;
	}
}
