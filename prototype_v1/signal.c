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


// void restore(void)
// {
//     tcsetattr(STDIN_FILENO, TCSANOW, &saved);
// }

void sig_qt_chld(int signum)
{
	(void)signum;
    // wait(NULL);
    ft_putstr_fd("Quit\n", 1);
}

void sig_int_prnt(int signum)
{

    (void)signum;
    // if (g_sig.sigva_1 != 1)
    // {
    // printf("g_sig.sigva_1 = %d\n", g_sig.sigva_1);
        ft_putstr_fd("\n", STDOUT_FILENO);
        rl_replace_line("", STDIN_FILENO);
        rl_on_new_line();
        rl_redisplay();
    // g_sig.sigva_1 = 2;
    // }
}

void sig_int_chld(int signum)
{

    (void)signum;
    // if (g_sig.sigva_1 != 1)
    // {
    // printf("g_sig.sigva_1 = %d\n", g_sig.sigva_1);
        ft_putstr_fd("\n", STDOUT_FILENO);
        // rl_replace_line("", STDIN_FILENO);
        // rl_on_new_line();
        // rl_redisplay();
    // g_sig.sigva_1 = 2;
    // }
}


void init_sig(void)
{
    // struct termios 	saved;
    // struct termios  attributes;

    // printf("hey\n");
    // tcgetattr(STDIN_FILENO, &attributes);
    // attributes.c_lflag &= ~ ECHOCTL;
    // tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
    // tcgetattr(STDIN_FILENO, &saved);
    signal(SIGINT, sig_int_prnt);
    signal(SIGQUIT, SIG_IGN);
    // tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
    // g_sig.sigva_1 = 2;
    // printf("sigint_child = %d\n", g_sig.sigint_child);
} 