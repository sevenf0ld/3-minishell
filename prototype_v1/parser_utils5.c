/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:04:34 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 18:56:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_multi_a(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;
	int		j;

	tmp = *tokens;
	j = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == CMD && c_node->args != NULL && j == 0)
			c_node->args[j++] = ft_strdup(tmp->token);
		else if (tmp->symbol == ARGS && c_node->args != NULL && j > 0)
			c_node->args[j++] = ft_strdup(tmp->token);
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
}

void	init_multi_a(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == ARGS || tmp->symbol == CMD)
			c_node->num_a += 1;
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_a > 0)
		c_node->args = malloc_err(sizeof(char *) * (c_node->num_a + 1),
				c_node->stat);
	if (c_node->args != NULL)
		c_node->args[c_node->num_a] = NULL;
	set_multi_a(tokens, c_node);
	remove_quotes(c_node->args);
}

static void	set_multi_l(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;
	int		j;

	tmp = *tokens;
	j = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == LIM && c_node->lim != NULL)
			c_node->lim[j++] = ft_strdup(tmp->token);
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
}

void	init_multi_l(t_mini *mi, t_token **tokens, t_command *c_node)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (tmp->symbol == LIM)
			c_node->num_l += 1;
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_l > 0)
		c_node->lim = malloc_err(sizeof(char *) * (c_node->num_l + 1),
				c_node->stat);
	if (c_node->lim != NULL)
        {
		c_node->lim[c_node->num_l] = NULL;
                mi->limiting = 1;
        }
	set_multi_l(tokens, c_node);
}
