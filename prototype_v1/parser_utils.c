/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:26:35 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/26 19:25:38 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * sets the files but not pipe read and write ends
 */
void	set_multi_fildes(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;
	int		i;
	int		j;
	int		k;

	tmp = *tokens;
	i = 0;
	j = 0;
	k = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == FILN && tmp->prev != NULL)
		{
			if (tmp->prev->symbol == IN_RE)
				c_node->std_in[i++] = open(tmp->token, O_RDONLY);
			if (tmp->prev->symbol == OUT_RE)
				c_node->std_out_o[j++] = open(tmp->token, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (tmp->prev->symbol == ADD)
				c_node->std_out_a[k++] = open(tmp->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		tmp = tmp->next;
	}
}

/*
 * init multi flags
 * init multi args
 * init multi redirections
 */
void	init_multi_redir(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == FILN && tmp->prev != NULL)
		{
			if (tmp->prev->symbol == IN_RE)
				c_node->num_si += 1;
			if (tmp->prev->symbol == OUT_RE)
				c_node->num_so_o += 1;
			if (tmp->prev->symbol == ADD)
				c_node->num_so_a += 1;
		}
		tmp = tmp->next;
	}
	if (c_node->num_si > 0)
		c_node->std_in = malloc(sizeof(int) * c_node->num_si);
	if (c_node->num_so_o > 0)
		c_node->std_in = malloc(sizeof(int) * c_node->num_so_o);
	if (c_node->num_so_a > 0)
		c_node->std_in = malloc(sizeof(int) * c_node->num_so_a);
	//set_multi_fildes(tokens, c_node);
}
