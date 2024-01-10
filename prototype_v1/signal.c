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

void sig_quit(int signum)
{
	(void)signum;
}

void sig_int(int signum)
{

    // printf("there\n");

    (void)signum;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_replace_line("", STDIN_FILENO);
    rl_on_new_line();
    rl_redisplay();

}


void init_sig(void)
{
    struct termios 	saved;
    struct termios  attributes;

    // printf("hey\n");
    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);tcgetattr(STDIN_FILENO, &saved);
    signal(SIGINT, sig_int);
    signal(SIGQUIT, SIG_IGN);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);

}