/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:35:29 by folim             #+#    #+#             */
/*   Updated: 2024/02/02 18:54:11 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_2d_arr(char **input)
{
	int	i;

	i = -1;
	while (input[++i])
		free(input[i]);
	free(input);
	input = NULL;
	return ;
}

void	free_tcmd(t_mini *mi)
{
	t_command	*curr;
	t_command	*next;

	if (!mi->cmd)
		return ;
	curr = mi->cmd;
	while (curr != NULL)
	{
		next = curr->next;
		free_2d_arr(curr->args);
		if (mi->limiting == 1)
		{
			free_2d_arr(curr->lim);
			mi->limiting = 0;
		}
		free(curr->og);
		free(curr->std_in);
		free(curr->std_out_o);
		free(curr->std_out_a);
		free(curr);
		curr = next;
	}
	return ;
}

void	free_ttkn(t_token **tkn)
{
	t_token	*curr;
	t_token	*next;

	if (!tkn || !*tkn)
		return ;
	curr = *tkn;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->token);
		free(curr);
		curr = next;
	}
	return ;
}

void	free_tpipe(t_pipe **pipe)
{
	t_pipe	*curr;
	t_pipe	*next;

	if (!pipe || !*pipe)
		return ;
	curr = *pipe;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	return ;
}

void	garbage_burner(t_mini *mi, char *pline)
{
	free(mi->pid->pid_c);
	free(mi->pid);
	free(pline);
	free_ttkn(&mi->tok_cpy);
	free_tcmd(mi);
	if (mi->piping == 1)
		free_tpipe(&mi->pip);
}
