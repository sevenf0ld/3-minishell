/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:36:05 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/04 15:27:42 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	delete_node_attach(t_token **lst, bool value)
{
	t_token	*curr;
	t_token	*to_remove;

	curr = *lst;
	while (curr->next != NULL)
	{
		while (curr->next->rm == value)
		{
			to_remove = curr->next;
			curr->next = curr->next->next;
			if (curr->next == NULL)
			{
				free(to_remove);
				return ;
			}
			free(to_remove);
			to_remove = NULL;
		}
		curr = curr->next;
	}
}

static void	delete_node(t_token **lst, bool value)
{
	t_token	*to_remove;

	if (*lst == NULL)
		return ;
	while ((*lst)->rm == value)
	{
		to_remove = (*lst);
		*lst = (*lst)->next;
		free(to_remove);
		to_remove = NULL;
	}
	delete_node_attach(lst, value);
}

/*
 * set the token boolean end to true so the space between two completed/terminated quotes are not mistaken as ARG
 * calls delete_node() which deletes the spaces between two string literals
 * so it doesnt confuse it as "1"2"3"4"5" but "1" "2" "3"
 */
void	manage_quotes(t_token **tokens)
{
	t_token	*tmp;
	int		num;

	tmp = *tokens;
	num = 0;
	while (tmp != NULL) 
	{
		if (!ft_strcmp(tmp->token, "\"") || !ft_strcmp(tmp->token, "'"))
		{
			num += 1;
			if (num == 2)
			{
				if (tmp->next != NULL)
					if (!is_delim(tmp->next->token[0]) && ft_iswhite(tmp->next->token[0]))
						tmp->next->rm = true;
				num = 0;
			}
		}
		tmp = tmp->next;
	}
	delete_node(tokens, true);
}

/*
 * detect and reject unterminated/incomplete quotes
 */
void	reject_unterminated_q(t_token **tokens, t_sym symbol)
{
	t_token	*tmp;
	t_token	*cur;
	int		num;

	tmp = *tokens;
	num = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == symbol)
		{
			num += 1;
			cur = tmp->next;
			while (cur != NULL)
			{
				if (cur->symbol == symbol)
				{
					num += 1;
					if (num == 2)
					{
						num = 0;
						tmp = cur;
						break ;
					}
				}
				cur = cur->next;
			}
		}
		tmp = tmp->next;
	}
	if (num == 1)
		quote_err();
}

/*
 * remove the quotes since expansion has taken place and the (outermost) quotes no longer serve a purpose
 */
void	delete_quotes_after_expand(t_token **tokens, t_sym symbol)
{
	t_token	*tmp;
	t_token	*cur;
	int		num;

	tmp = *tokens;
	num = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == symbol)
		{
			num += 1;
			cur = tmp->next;
			while (cur != NULL)
			{
				if (cur->symbol == symbol)
				{
					num += 1;
					break ;
				}
				cur = cur->next;
			}
			if (num == 2)
			{
				tmp->rm = true;
				cur->rm = true;
				num = 0;
				tmp = cur;
				continue ;
			}
		}
		tmp = tmp->next;
	}
	delete_node(tokens, true);
}
