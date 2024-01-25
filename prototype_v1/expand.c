/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2024/01/25 19:43:01 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	expand_env_var(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->exp && ft_strcmp(tmp->token, "$?") != 0)
                {
                    //fprintf(stderr, "TMP->TOKEN 1 %s\n", tmp->token);
			tmp->token = expand_utils(&tmp->token, 0);
                    //fprintf(stderr, "TMP->TOKEN 2 %s\n", tmp->token);
                }
		else if (tmp->exp && !ft_strcmp(tmp->token, "$?"))
			tmp->token = ft_lltoa(tmp->stat->s_code);
		tmp = tmp->next;
	}
}

void	expansion(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->token, '$'))
                    tmp->exp = true;
		tmp = tmp->next;
	}
	expand_env_var(tokens);
}
