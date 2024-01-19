/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:48:46 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 19:02:09 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_command	*cmd_new(char *cmd, int n, t_env *envs, t_status *stat)
{
	t_command	*node;

	node = malloc_err(sizeof(t_command), stat);
	node->pos = n;
	node->size = 0;
	node->cmd = cmd;
	node->args = NULL;
	node->num_a = 0;
	node->lim = NULL;
	node->num_l = 0;
	node->std_in = NULL;
	node->num_si = 0;
	node->std_out_o = NULL;
	node->num_so_o = 0;
	node->std_out_a = NULL;
	node->num_so_a = 0;
	node->read_end = -1;
	node->write_end = -1;
	node->og = NULL;
	node->builtin = is_builtin(cmd);
	node->last_out = INT_MIN;
        node->exec = true;
	node->env_var = envs;
	node->stat = stat;
	node->next = NULL;
	return (node);
}

void	cmd_add_back(t_command **head, t_command *node)
{
	t_command	*old_end;

	if (!node)
		return ;
	old_end = cmd_last(*head);
	old_end->next = node;
}

static void set_cmd_size(t_command *head)
{
	int			n;
	t_command	*tmp;

	n = cmd_size(head);
	tmp = head;
	while (tmp != NULL)
	{
		tmp->size = n;
		tmp = tmp->next;
	}
}

static char *cmd_init_norme(t_token *first)
{
    t_token *tmp;
    char    *cmd;

    tmp = first;
    cmd = NULL;
    while (tmp != NULL && tmp->symbol != PIPE)
    {
        if (tmp->symbol == CMD)
            cmd = tmp->token;
        tmp = tmp->next;
    }
    return (cmd);
}

static int  num_pipes(t_token **tokens)
{
    t_token *tmp;
    int     i;

    tmp = *tokens;
    i = 0;
    while (tmp != NULL)
    {
        if (tmp->symbol == PIPE)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

/*
 * converts the categorized and grouped tokens into individual command sets/groups
 */
void    cmd_init(t_token **tokens, t_command **cmds, t_env *envs, t_status *stat)
{
    t_token *tmp;
    t_token *first;
    int     i;

    tmp = *tokens;
    first = *tokens;
    i = 0;
    while (tmp != NULL)
    {
        if (tmp->symbol == PIPE)
        {
            if (i == 0)
                    *cmds = cmd_new(cmd_init_norme(first), i, envs, stat);
            else
                    cmd_add_back(cmds, cmd_new(cmd_init_norme(first), i, envs, stat));
            i++;
            first = tmp->next;
            if (i == num_pipes(tokens))
                cmd_add_back(cmds, cmd_new(cmd_init_norme(first), i, envs, stat));
        }
        tmp = tmp->next;
    }
    if (num_pipes(tokens) == 0)
        *cmds = cmd_new(cmd_init_norme(first), i, envs, stat);
    set_cmd_size(*cmds);
}

t_command	*cmd_last(t_command *head)
{
	t_command	*tmp;

	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	cmd_size(t_command *head)
{
	t_command	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
