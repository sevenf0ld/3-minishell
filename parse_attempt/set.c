/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:14:52 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/14 11:55:04 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

void	set_split_type_one(t_split **splits, int (f)(char *s, char *t))
{
	t_split	*tmp;

	tmp = *splits;
	tmp->symbol = CMD;
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
		tmp = tmp->next;
	}
	set_split_type_two(splits);
}

/*
 * echo message
 * 0 2
 * ls test.txt
 * 0 8
 */
void	set_split_type_two(t_split **splits)
{
	t_split	*tmp;

	tmp = *splits;
	while (tmp != NULL)
	{
		if (tmp->symbol == OUTREDIR || tmp->symbol == INREDIR || tmp->symbol == ADDEND)
			if (tmp->next != NULL)
				tmp->next->symbol = FILN;

		if (tmp->symbol == FILN && tmp->next != NULL)
				tmp->next->symbol = CMD;
		if ((int)tmp->symbol == -1)
			tmp->symbol = MSG;
		tmp = tmp->next;
	}
}
