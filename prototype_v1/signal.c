/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:59 by folim             #+#    #+#             */
/*   Updated: 2024/01/31 17:51:51 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void sig_qt_chld(int signum)
{
    (void)signum;
    ft_putstr_fd("Quit\n", STDERR_FILENO);
    g_sig.sig_qt = true;
    g_sig.sig_int = false;
    g_sig.sig_code = 0;
}

void sig_int_prnt(int signum)
{

    (void)signum;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_replace_line("", STDIN_FILENO);
    rl_on_new_line();
    rl_redisplay();
    g_sig.sig_int = true;
    g_sig.sig_qt = false;
    g_sig.sig_code = 130;
}

void sig_int_chld(int signum)
{
    (void)signum;
    ft_putstr_fd("\n", STDOUT_FILENO);
    g_sig.sig_int = true;
    g_sig.sig_qt = false;
    g_sig.sig_code = 130;
}

void    sig_qt_prnt(int signum)
{
    (void) signum;
    rl_redisplay();
    ft_putstr_fd("  \b\b", STDOUT_FILENO);
    g_sig.sig_qt = true;
    g_sig.sig_int = false;
    g_sig.sig_code = 0;
}
