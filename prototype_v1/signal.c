/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:59 by folim             #+#    #+#             */
/*   Updated: 2024/02/01 15:36:53 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	sig_qt_prnt(int signum)
{
	(void)signum;
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
	g_sig.sig = true;
}

static void	sig_int_prnt(int signum)
{
	(void)signum;
	ft_putendl_fd(NULL, STDOUT_FILENO);
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_sig.sig = true;
	g_sig.sig_code = 130;
}

void	signal_parent(void)
{
	signal(SIGQUIT, sig_qt_prnt);
	signal(SIGINT, sig_int_prnt);
}

static void	sig_qt_chld(int signum)
{
	(void)signum;
	ft_putendl_fd("Quit", STDERR_FILENO);
}

static void	sig_int_chld(int signum)
{
	(void)signum;
	ft_putendl_fd(NULL, STDOUT_FILENO);
}

void	signal_child(void)
{
	signal(SIGQUIT, sig_qt_chld);
	signal(SIGINT, sig_int_chld);
}
