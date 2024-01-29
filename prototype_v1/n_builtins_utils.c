/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:13:30 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/29 23:28:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//n_builtins_2
static void    mini_exec_nb(t_command *c_node, t_mini *mi)
{
    if (!ft_strcmp(c_node->cmd, "echo"))
        b_echo(c_node, mi);
    else if (!ft_strcmp(c_node->cmd, "pwd"))
        b_pwd(c_node, 'w', mi);
    else if (!ft_strcmp(c_node->cmd, "cd") && c_node->size > 1)
        b_cd(c_node, mi);
    else if (!ft_strcmp(c_node->cmd, "env"))
        b_env(c_node, &mi->fix, mi);
    else if (!ft_strcmp(c_node->cmd, "unset"))
        b_unset(c_node, &mi->fix, mi);
    else if (!ft_strcmp(c_node->cmd, "export") && c_node->size > 1)
        b_export(c_node, &mi->fix, mi);
    else if (!ft_strcmp(c_node->cmd, "exit") && c_node->size > 1)
        b_exit(c_node, mi);
}

//n_builtins_2
int mini_exec(t_command *c_node, t_mini *mi, char **envp)
{
    pid_t   *child;

    child = mi->pid->pid_c;
    signal(SIGINT, sig_int_chld);
    signal(SIGQUIT, sig_qt_chld);
    child[c_node->pos] = fork();
    if (child[c_node->pos] == -1)
    {
        exit(EXIT_FAILURE);
        return (1);
    }
    if (child[c_node->pos] == 0)
    {
        close_unused_ends(&mi->cmd, c_node->pos);
        redirect_command_io(c_node);
        if (!c_node->builtin)
        {
            execve(c_node->args[0], c_node->args, envp);
            exit(EXIT_FAILURE);
        }
        else
        {
            mini_exec_nb(c_node, mi);
            exit(mi->stat->s_code);
        }
    }
    return (0);
}
