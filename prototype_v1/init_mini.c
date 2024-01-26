/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:36:30 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 12:40:58 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void    mini_init_stat_res(t_mini *mi)
{
    mi->stat = malloc_err(sizeof(t_status), mi->stat);
    mi->stat->s_code = 0;
    mi->res = malloc_err(sizeof(t_restore), mi->stat);
    mi->res->std_out = -1;
    mi->res->std_in = -1;
}

void    mini_init_environ(t_mini *mi, char **envp)
{
    f_init(&mi->fix, envp, mi->stat);
    env_init(&mi->env, envp, mi->fix, mi->stat);
}

void    mini_init_pid(t_mini *mi)
{
    mi->pid = malloc_err(sizeof(t_pid), mi->stat);
    mi->pid->pid_c = malloc_err(sizeof(pid_t) * (mi->cmd->size), mi->stat);
}
