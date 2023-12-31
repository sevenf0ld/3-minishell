/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:48:46 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/31 16:06:07 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * use an array of cmds to make it shorter
 */
static bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (true);
	else if (!ft_strcmp(cmd, "cd"))
		return (true);
	else if (!ft_strcmp(cmd, "pwd"))
		return (true);
	else if (!ft_strcmp(cmd, "export"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	else if (!ft_strcmp(cmd, "env"))
		return (true);
	else if (!ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

t_command	*cmd_new(char *cmd, int n, t_env *envs, t_status *stat)
{
	t_command	*node;

	node = malloc_err(sizeof(t_command), stat);
	node->pos = n;
	node->size = 0;
	node->cmd = cmd;
	node->flags = NULL;
	node->num_f = 0;
	node->args = NULL;
	node->num_a = 0;
	node->lim = NULL;
	node->std_in = NULL;
	node->num_si = 0;
	node->std_out_o = NULL;
	node->num_so_o = 0;
	node->std_out_a = NULL;
	node->num_so_a = 0;
	node->read_end = -1;
	node->write_end = -1;
	node->og = NULL;
	node->builtin = is_builtin(node->cmd);
	node->last_out = INT_MIN;
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

void	set_cmd_size(t_command *head)
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

/*
 * converts the categorized and grouped tokens into individual command sets/groups
 */
/*
void	cmd_init(t_token **tokens, t_command **cmds, t_env *envs, t_status *stat)
{
	t_token		*tmp;
	int			i;

	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == CMD)
		{
			if (i == 0)
				*cmds = cmd_new(tmp->token, i, envs, stat);
			else
				cmd_add_back(cmds, cmd_new(tmp->token, i, envs, stat));
			i++;
		}
		tmp = tmp->next;
	}
	set_cmd_size(*cmds);
}
*/

///*
void    cmd_init(t_token **tokens, t_command **cmds, t_env *envs, t_status *stat)
{

    char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
    t_token *tmp;
    int     i;
    char    *cmd;
    t_token *cur;

    tmp = *tokens;
    i = 0;
    cur = *tokens;
    (void) cmds;
    (void) envs;
    (void) stat;
    while (tmp != NULL)
    {
        if (cur != NULL)
            fprintf(stderr, "cur is now %s of type %s\n", cur->token, type[cur->symbol]);
        cmd = NULL;
        while (cur != NULL)
        {
            if (cur->symbol == PIPE)
            {
                fprintf(stderr, "\x1b[35mfound a pipe\x1b[m\n");
                break ;
            }
            if (cur->symbol == CMD)
            {
                cmd = cur->token;
                fprintf(stderr, "\x1b[35mfound the command %s\x1b[m\n", cur->token);
                if (i == 0)
                    //*cmds = cmd_new(cmd, i, envs, stat);
                    fprintf(stderr, "\x1b[33m%s for index 0 with %s\x1b[m\n", cur->token, cmd);
                else
                    //cmd_add_back(cmds, cmd_new(cmd, i, envs, stat));
                    fprintf(stderr, "\x1b[43m%s for index %i with %s\x1b[m\n", cur->token, i, cmd);
                i++;
            }
            cmd = NULL;
            cur = cur->next;
        }
        tmp = tmp->next;
        if (cur != NULL)
            cur = cur->next;
    }
}
//*/

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
