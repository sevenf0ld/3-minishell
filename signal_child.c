/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:11:59 by folim             #+#    #+#             */
/*   Updated: 2024/02/02 16:21:25 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
