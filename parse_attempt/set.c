/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:14:52 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/11 16:21:26 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

//for msgs, check if before or after is 4 - 6
void	set_split_type(t_split **splits, int (f)(char *s, char *t))
{
	t_split	*tmp;

	tmp = *splits;
	tmp->symbol = CMD;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (tmp->each[0] == '-')
			tmp->symbol = OPT;
		else if (!f(tmp->each, "|"))
			tmp->symbol = PIPE;
		else if (!f(tmp->each, ">"))
			tmp->symbol = OUTREDIR;
		else if (!f(tmp->each, "<"))
			tmp->symbol = INREDIR;
		else if (!f(tmp->each, ">>"))
			tmp->symbol = ADDEND;
		else if (!f(tmp->each, "<<"))
			tmp->symbol = HEREDOC;
		else
			tmp->symbol = MSG;
		tmp = tmp->next;
	}
}
