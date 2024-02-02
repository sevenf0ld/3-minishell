/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:39:03 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/22 15:01:28 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*cmd_init_norme_three(t_token *first)
{
	char	*cmd;
	t_token	*tmp;

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

static int	num_pipes(t_token **tokens)
{
	int		i;
	t_token	*tmp;

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

static void	cmd_init_norme_one(t_cmd_norme *cmd_params, t_token **token)
{
	cmd_params->i = 0;
	cmd_params->tmp = *token;
	cmd_params->first = *token;
	cmd_params->tokens = token;
}

static void	cmd_init_norme_two(t_cmd_norme *cmd_params)
{
	t_command	*tmp_cmd;

	if (cmd_params->i == 0)
		*cmd_params->cmds = cmd_new(cmd_init_norme_three(cmd_params->first),
									cmd_params->i,
									cmd_params->envs,
									cmd_params->stat);
	else
	{
		tmp_cmd = cmd_new(cmd_init_norme_three(cmd_params->first),
							cmd_params->i,
							cmd_params->envs,
							cmd_params->stat);
		cmd_add_back(cmd_params->cmds, tmp_cmd);
	}
	cmd_params->i++;
	cmd_params->first = cmd_params->tmp->next;
	if (cmd_params->i == num_pipes(cmd_params->tokens))
	{
		tmp_cmd = cmd_new(cmd_init_norme_three(cmd_params->first),
							cmd_params->i,
							cmd_params->envs,
							cmd_params->stat);
		cmd_add_back(cmd_params->cmds, tmp_cmd);
	}
}

void	cmd_init(t_token **t, t_command **cmds, t_env *envs, t_status *stat)
{
	t_cmd_norme	cmd_params;

	cmd_params = (t_cmd_norme){0};
	cmd_init_norme_one(&cmd_params, t);
	cmd_params.cmds = cmds;
	cmd_params.envs = envs;
	cmd_params.stat = stat;
	while (cmd_params.tmp != NULL)
	{
		if (cmd_params.tmp->symbol == PIPE)
			cmd_init_norme_two(&cmd_params);
		cmd_params.tmp = cmd_params.tmp->next;
	}
	if (num_pipes(t) == 0)
		*cmds = cmd_new(cmd_init_norme_three(cmd_params.first), cmd_params.i,
				envs, stat);
	set_cmd_size(*cmds);
}
