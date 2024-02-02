/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:17 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 16:21:10 by maiman-m         ###   ########.fr       */
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
