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

void sig_int(int signum)
{
	(void)signum;
	ft_putstr_fd("\b\b  \nminishell > ", STDERR_FILENO);
}

void sig_quit(int signum)
{
	(void)signum;
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}