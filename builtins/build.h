/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 00:14:19 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 21:27:58 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_H
# define BUILD_H

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

//lexer
typedef struct s_token
{
	char				*token;
	struct s_token		*next;
}						t_token;			

//parser
typedef struct	s_command
{
	char				*cmd;
	char				*flags;
	char				*input;
	int					std_in;
	int					std_out;
	int					std_err;
	int					order;
	struct s_command	*next;
}						t_command;

//lexer
t_token		*token_new(char *token);
void		token_add_back(t_token **head, t_token *node);
void		token_init(char **args, t_token **head);
t_token		*token_last(t_token *head);
int			token_size(t_token *head);

//parser
t_command	*cmd_new(char *cmd);
void		cmd_add_back(t_command **head, t_command *node);
void		cmd_init(char **args, t_command **head);
t_command	*cmd_last(t_command *head);
int			cmd_size(t_command *head);

#endif
