/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:43:53 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/21 00:13:18 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_pipe	*pipe_new(int n)
{
	t_pipe	*node;

	node = malloc_err(sizeof(t_pipe));
	node->pos = n;
	pipe_err(node->pipe_fd);
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

void	pipe_init(t_pipe **pipes, int loop)
{
	t_pipe	*tmp;
	int		i;

	tmp = *pipes;
	i = 0;
	while (i < loop)
	{
		if (i == 0)
			*pipes = pipe_new(i);
		else
			pipe_add_back(pipes, pipe_new(i));
		i++;
	}
}
