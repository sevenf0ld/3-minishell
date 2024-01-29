/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:59 by folim             #+#    #+#             */
/*   Updated: 2024/01/29 23:41:32 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void sig_qt_chld(int signum)
{
	(void)signum;
    ft_putstr_fd("Quit\n", STDERR_FILENO);
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

void    sig_qt_prnt(int signum)
{
    (void) signum;
    rl_redisplay();
    ft_putstr_fd("  \b\b  \b\b", STDOUT_FILENO);
}
