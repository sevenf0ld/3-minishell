/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:14:19 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 00:53:51 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#ifndef LEX_H
# define LEX_H

typedef struct s_list
{
	char				*cmd;
	struct s_list		*next;
}						t_list;			

t_list		*sl_initialize(char **args, t_list *head);
t_list		*sl_last(t_list *head);
int			sl_size(t_list *head);
t_list		*sl_new(t_list *head, char *token);
void		sl_add_back(t_list **head, char *token);
#endif
