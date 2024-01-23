/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/23 15:13:19 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	decide_word(char c, bool *sq, bool *wq)
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

void	expand_utils(char *s, t_status *stat)
{
	int		i = 0;
	bool	sq = false;
	bool	wq = false;
	
	(void) stat;
	(void) sq;
	(void) wq;
	(void) decide_word;
	fprintf(stderr, "\x1b[32m s: %s, strchr: %s \x1b[m\n", s, ft_strchr(s, '$'));

	while (s[i] != '\0')
	{
		decide_word(s[i], &sq, &wq);
		if (sq)
			break ;
		i++;
	}
	fprintf(stderr, "\x1b[42m s: %s \x1b[m\n", s + i);
}
