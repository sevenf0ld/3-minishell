/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reject_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:27:20 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 02:50:15 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	decide_quote(char c, bool *sq, bool *wq)
{
	if (c == 39 && !*sq && !*wq)
		*sq = true;
	else if (c == 34 && !*wq && !*sq)
		*wq = true;
	else if (c == 39 && *sq && !*wq)
		*sq = false;
	else if (c == 34 && *wq && !*sq)
		*wq = false;
}

static int	unterm_q_norme(bool sq, bool wq, t_status *stat)
{
	if (sq && !wq)
		return (quote_err("\'", stat));
	else if (wq && !sq)
		return (quote_err("\"", stat));
	return (0);
}

static void	reset_unterm_params(t_unterm_norme *unterm_params)
{
	unterm_params->i = 0;
	unterm_params->sq = false;
	unterm_params->wq = false;
}

static int  not_symbol(t_sym symbol)
{
    if (symbol == CMD || symbol == ARGS)
        return (1);
    if (symbol == FILN || symbol == LIM)
        return (1);
    return (0);
}

int	unterminated_quotes(t_token *t_node, t_status *stat)
{
	t_unterm_norme	unterm_params;

	unterm_params = (t_unterm_norme){0, false, false, NULL, t_node};
	while (unterm_params.tmp != NULL)
	{
		//if (unterm_params.tmp->symbol == ARGS)
		if (not_symbol(unterm_params.tmp->symbol))
		{
			unterm_params.s = unterm_params.tmp->token;
			reset_unterm_params(&unterm_params);
			while (unterm_params.s[unterm_params.i] != '\0')
			{
				if (unterm_params.s[unterm_params.i] == 39
					|| unterm_params.s[unterm_params.i] == 34)
					decide_quote(
						unterm_params.s[unterm_params.i],
						&unterm_params.sq,
						&unterm_params.wq);
				unterm_params.i++;
			}
			if (unterm_q_norme(unterm_params.sq, unterm_params.wq, stat))
				return (1);
		}
		unterm_params.tmp = unterm_params.tmp->next;
	}
	return (0);
}
