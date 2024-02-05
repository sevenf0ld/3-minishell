/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:43:53 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/30 12:43:28 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_pipe	*pipe_new(int n, t_status *stat)
{
	t_pipe	*node;

	node = malloc_err(sizeof(t_pipe), stat);
	node->pos = n;
	pipe_err(node->pipe_fd, stat);
	node->next = NULL;
	return (node);
}

t_pipe	*pipe_last(t_pipe *head)
{
	t_pipe	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	pipe_add_back(t_pipe **head, t_pipe *node)
{
	t_pipe	*old_end;

	if (!node)
		return ;
	old_end = pipe_last(*head);
	old_end->next = node;
}

/*
 * initializes pipes based on the amount of t_command nodes - 1
 */
void	pipe_init(t_pipe **pipes, int loop, t_status *stat)
{
	int	i;

	i = 0;
	while (i < loop)
	{
		if (i == 0)
			*pipes = pipe_new(i, stat);
		else
			pipe_add_back(pipes, pipe_new(i, stat));
		i++;
	}
}
