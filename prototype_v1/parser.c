/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:07:39 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 13:27:58 by maiman-m         ###   ########.fr       */
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
	    c_node->args = malloc_err(sizeof(char *) * (c_node->num_a + 1), c_node->stat);
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
	    c_node->lim = malloc_err(sizeof(char *) * (c_node->num_l + 1), c_node->stat);
	if (c_node->lim != NULL)
	{
		c_node->lim[c_node->num_l] = NULL;
		mi->limiting = 1;
	}
	set_multi_l(tokens, c_node);
}

static char	*join_and_free(char *to_free, char *to_concat)
{
	char	*end;

	end = ft_strjoin(to_free, to_concat);
	free(to_free);
	to_free = NULL;
	return (end);
}

static char	*rm_till_end(t_token **tokens)
{
	t_token	*tmp;
	char	*ret;
	char	*trim;

	tmp = *tokens;
	ret = ft_strdup("");
	while (tmp != NULL && tmp->end == false)
	{
		ret = join_and_free(ret, tmp->token);
		ret = join_and_free(ret, " ");
		*tokens = tmp->next;
		// free(tmp);
		tmp = NULL;
		tmp = *tokens;
	}
	if (tmp != NULL && tmp->end == true)
	{
		*tokens = tmp->next;
		// free(tmp);
		tmp = NULL;
	}
	trim = ft_strtrim(ret, " ");
	free(ret);
	return (trim);
}

/*
 * calls init_multi_fa() which stores all the flags (OPT) and arguments (ARGS) in its respective 2D char array (end marker is NULL)
 * calls init_multi_redir() which stores all the input and output (overwrite & append) redirections in its respect int array (end marker is INT_MIN)
 */
void	complete_cmd(t_mini *mi, t_token **tokens, t_command **cmds)
{
	t_command	*c_node;

	c_node = *cmds;
	while (c_node != NULL)
	{
		init_multi_a(tokens, c_node);
		init_multi_l(mi, tokens, c_node);
		init_multi_redir(tokens, c_node);
		c_node->og = rm_till_end(tokens);
		c_node = c_node->next;
	}	
}

static void update_cmd_exec(t_command **cmds)
{
    t_command   *c_node;

    c_node = *cmds;
    while (c_node != NULL)
    {
        if (!c_node->cmd)
            c_node->exec = false;
        c_node = c_node->next;
    }
}

//t_pipe *parser(t_token **tokens, t_command **cmds, t_env *envs, t_status *stat)
void    parser(t_mini *mi)
{
        t_token     **tokens;
	t_command   **cmds;

        tokens = &mi->tok;
	cmds = &mi->cmd;
	cmd_init(tokens, cmds, mi->env, mi->stat);
        update_cmd_exec(cmds);
	double_ll_convert2(cmds);
	mi->limiting = 0;
	complete_cmd(mi, tokens, cmds);
	mi->piping = 0;
	if (*cmds != NULL && (*cmds)->size > 1)
	{
		pipe_init(&mi->pip, (*cmds)->size - 1, mi->stat);
		double_ll_convert3(&mi->pip);
		assign_pipe_ends(*cmds, mi->pip);
		mi->piping = 1;
	}
}
