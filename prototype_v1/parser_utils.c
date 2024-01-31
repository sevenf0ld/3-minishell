/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:26:35 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/31 14:11:04 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	set_multi_fildes_norme(t_fildes_norme *fildes_params, int i)
{
        rm(&fildes_params->tmp->token, 0);
	if (i == 0)
	{
		if (fildes_params->tmp->prev->symbol == IN_RE)
			fildes_params->c_node->std_in[fildes_params->i++] = open_err(
					fildes_params->tmp->token, O_RDONLY, 0444, fildes_params->c_node);
		if (fildes_params->tmp->prev->symbol == OUT_RE)
		{
			fildes_params->c_node->std_out_o[fildes_params->j++] = open_err(
					fildes_params->tmp->token, O_CREAT | O_WRONLY
					| O_TRUNC, 0777, fildes_params->c_node);
			fildes_params->c_node->last_out = fildes_params->c_node->std_out_o[fildes_params->j - 1];
		}
		if (fildes_params->tmp->prev->symbol == ADD)
		{
			fildes_params->c_node->std_out_a[fildes_params->k++] = open_err(
					fildes_params->tmp->token, O_CREAT | O_WRONLY
					| O_APPEND, 0666, fildes_params->c_node);
			fildes_params->c_node->last_out = fildes_params->c_node->std_out_a[fildes_params->k - 1];
		}
	}
}

void	set_multi_fildes(t_token **tokens, t_command *c_node)
{
	t_fildes_norme	fildes_params;

	fildes_params = (t_fildes_norme){0};
	fildes_params.tmp = *tokens;
	fildes_params.c_node = c_node;
	fildes_params.tokens = tokens;
	while (fildes_params.tmp != NULL)
	{
		if (fildes_params.tmp->symbol == FILN && fildes_params.tmp->prev != NULL)
			set_multi_fildes_norme(&fildes_params, 0);
		if (fildes_params.tmp->end == true)
			break ;
		fildes_params.tmp = fildes_params.tmp->next;
	}
	if (fildes_params.c_node->num_si > 0)
		fildes_params.c_node->std_in[fildes_params.i] = INT_MIN;
	if (fildes_params.c_node->num_so_o > 0)
		fildes_params.c_node->std_out_o[fildes_params.j] = INT_MIN;
	if (fildes_params.c_node->num_so_a > 0)
		fildes_params.c_node->std_out_a[fildes_params.k] = INT_MIN;
}

void	init_multi_redir_norme(t_token *t_node, t_command *c_node)
{
	if (t_node->symbol == FILN && t_node->prev != NULL)
	{
		if (t_node->prev->symbol == IN_RE)
			c_node->num_si += 1;
		if (t_node->prev->symbol == OUT_RE)
			c_node->num_so_o += 1;
		if (t_node->prev->symbol == ADD)
			c_node->num_so_a += 1;
	}
}

void	init_multi_redir(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		init_multi_redir_norme(tmp, c_node);
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_si > 0)
		c_node->std_in = malloc_err(
				sizeof(int) * (c_node->num_si + 1), c_node->stat);
	if (c_node->num_so_o > 0)
		c_node->std_out_o = malloc_err(
				sizeof(int) * (c_node->num_so_o + 1), c_node->stat);
	if (c_node->num_so_a > 0)
		c_node->std_out_a = malloc_err(
				sizeof(int) * (c_node->num_so_a + 1), c_node->stat);
	set_multi_fildes(tokens, c_node);
}

