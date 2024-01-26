/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:48:46 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 13:44:51 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void cmd_new_norme_one(t_command *node, int n, char *cmd)
{
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
}

static void cmd_new_norme_two(t_command *node)
{
	node->num_so_o = 0;
	node->std_out_a = NULL;
	node->num_so_a = 0;
	node->read_end = -1;
	node->write_end = -1;
	node->og = NULL;
        node->builtin = is_builtin(node->cmd);
	node->last_out = INT_MIN;
	node->exec = true;
}

t_command	*cmd_new(char *cmd, int n, t_env *envs, t_status *stat)
{
	t_command	*node;

	node = malloc_err(sizeof(t_command), stat);
        cmd_new_norme_one(node, n, cmd);
        cmd_new_norme_two(node);
	node->env_var = envs;
	node->stat = stat;
	node->next = NULL;
	return (node);
}
