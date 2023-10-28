/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:26:35 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/28 13:16:35 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * need to add error handling for open
 */
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
				c_node->std_in[i++] = open(tmp->token, O_RDONLY);
			if (tmp->prev->symbol == OUT_RE)
				//*(c_node->std_out_o++) = open(tmp->token, O_CREAT | O_WRONLY | O_TRUNC, 0777);
				c_node->std_out_o[j++] = open(tmp->token, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (tmp->prev->symbol == ADD)
				//*(c_node->std_out_a++) = open(tmp->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
				c_node->std_out_a[k++] = open(tmp->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
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

/*
 * init multi I/O redirections excluding pipes
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
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_si > 0)
		c_node->std_in = malloc(sizeof(int) * (c_node->num_si + 1));
	if (c_node->num_so_o > 0)
		c_node->std_out_o = malloc(sizeof(int) * (c_node->num_so_o + 1));
	if (c_node->num_so_a > 0)
		c_node->std_out_a = malloc(sizeof(int) * (c_node->num_so_a + 1));
	set_multi_fildes(tokens, c_node);
}
