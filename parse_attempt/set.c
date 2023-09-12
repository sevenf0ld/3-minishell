/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:14:52 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/12 17:10:32 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build.h"

/*
 * for msgs, check if before or after is 4 - 6
 * if before, the msg is a file
 * < infile ls -l | wc -l > outfile 
 * msgs can be either a command or a file
 * after a file must be command
 */
void	set_split_type_one(t_split **splits, int (f)(char *s, char *t))
{
	t_split	*tmp;

	tmp = *splits;
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
	set_split_type_two(splits);
}

void	set_split_type_two(t_split **splits)
{
	t_split	*tmp;

	tmp = *splits;
	if (tmp && tmp->next == NULL)
	{
		tmp->symbol = CMD;
		return ;
	}
	while (tmp != NULL)
	{
		if (tmp->symbol == OUTREDIR || tmp->symbol == INREDIR || tmp->symbol == ADDEND)
			if (tmp->next != NULL)
				tmp->next->symbol = FILN;
		if (tmp->symbol == FILN && tmp->next != NULL)
				tmp->next->symbol = CMD;
		if (tmp->next != NULL && tmp->symbol != OPT && tmp->next->symbol == OPT)
			tmp->symbol = CMD;
		tmp = tmp->next;
	}
}
