/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concurrent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 08:01:50 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 12:04:25 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	close_unused_ends(t_command **cmds, int i)
{
	t_command	*cur;

	(void)print_inode;
	cur = *cmds;
	while (cur != NULL)
	{
		if (cur->pos != i)
		{
			if (cur->pos == 0)
				close_err(cur->write_end, cur->stat);
			else if (cur->pos == cur->size - 1)
				close_err(cur->read_end, cur->stat);
			else
			{
				close_err(cur->write_end, cur->stat);
				close_err(cur->read_end, cur->stat);
			}
		}
		cur = cur->next;
	}
}

void	last_close(t_pipe **pipes, t_mini *mi)
{
	t_pipe	*tmp;

	tmp = *pipes;
	while (tmp != NULL)
	{
		close_err(tmp->pipe_fd[0], mi->stat);
		close_err(tmp->pipe_fd[1], mi->stat);
		tmp = tmp->next;
	}
}
