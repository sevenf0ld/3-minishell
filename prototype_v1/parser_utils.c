/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:26:35 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 15:54:17 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_multi_fildes(t_token **tokens, t_command *c_node)
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
				c_node->std_in[i++] = open_err(tmp->token, O_RDONLY, 0444, c_node);
			if (tmp->prev->symbol == OUT_RE)
			{
				//*(c_node->std_out_o++) = open(tmp->token, O_CREAT | O_WRONLY | O_TRUNC, 0777);
				c_node->std_out_o[j++] = open_err(tmp->token, O_CREAT | O_WRONLY | O_TRUNC, 0777, c_node);
				c_node->last_out = c_node->std_out_o[j - 1];
			}
			if (tmp->prev->symbol == ADD)
			{
				//*(c_node->std_out_a++) = open(tmp->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
				c_node->std_out_a[k++] = open_err(tmp->token, O_CREAT | O_WRONLY | O_APPEND, 0666, c_node);
				c_node->last_out = c_node->std_out_a[k - 1];
			}
		}
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_si > 0)
		//*(c_node->std_in) = INT_MIN;
		c_node->std_in[i] = INT_MIN;
	if (c_node->num_so_o > 0)
		//*(c_node->std_out_o) = INT_MIN;
		c_node->std_out_o[j] = INT_MIN;
	if (c_node->num_so_a > 0)
		//*(c_node->std_out_a) = INT_MIN;
		c_node->std_out_a[k] = INT_MIN;
}

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
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_si > 0)
		c_node->std_in = malloc_err(sizeof(int) * (c_node->num_si + 1), c_node->stat);
	if (c_node->num_so_o > 0)
		c_node->std_out_o = malloc_err(sizeof(int) * (c_node->num_so_o + 1), c_node->stat);
	if (c_node->num_so_a > 0)
		c_node->std_out_a = malloc_err(sizeof(int) * (c_node->num_so_a + 1), c_node->stat);
	set_multi_fildes(tokens, c_node);
}
