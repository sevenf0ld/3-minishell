/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:59 by folim             #+#    #+#             */
/*   Updated: 2023/11/10 22:17:41 by folim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void sig_qt_chld(int signum)
{
	(void)signum;
    ft_putstr_fd("Quit\n", 1);
}

void sig_int_prnt(int signum)
{

    (void)signum;
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_replace_line("", STDIN_FILENO);
        rl_on_new_line();
        rl_redisplay();
}

void sig_int_chld(int signum)
{
    (void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
}


void init_sig(void)
{
    signal(SIGINT, sig_int_prnt);
    signal(SIGQUIT, SIG_IGN);
} 