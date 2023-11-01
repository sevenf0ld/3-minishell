/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:34:44 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/01 18:38:21 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * loop ends on INT_MIN
 */
static void	redirect_io_file(int *fd_arr, char mode)
{
	int	i;
	
	i = 0;
	while (fd_arr[i] != INT_MIN)
		i++;
	if (mode == 'i')
		dup2_err(fd_arr[i - 1], STDIN_FILENO);
	else if (mode == 'o')
		dup2_err(fd_arr[i - 1], STDOUT_FILENO);
}

/*
 * if size is one means there is no pipe
 * 		redir only involves files if any
 * if not NULL means there is a redirection
 * 		iterate until before INT_MIN and dup2 STDIN/STDOUT_FILENO
 * 		make a distinction between out_re and add?
 */
void	handle_redirections(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->std_in != NULL)
			redirect_io_file(cur->std_in, 'i');
		if (cur->std_out_o != NULL)
			redirect_io_file(cur->std_out_o, 'o');
		if (cur->std_out_a != NULL)
			redirect_io_file(cur->std_out_a, 'o');
		cur = cur->next;
	}
}
