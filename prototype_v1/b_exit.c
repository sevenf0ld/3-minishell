/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:33:37 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 09:02:41 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	exit_argless(t_command *c_node, t_mini *mi)
{
	mi->stat->s_code = 0;
	conditional_exit_display(c_node->size);
	garbage_burner(mi);
	exit(mi->stat->s_code);
	return ;
}

static void	rm_plus_sign(char **s)
{
	char	*tmp;
	int		i;

	if (*s[0] != 43 || *s[0] == 45)
		return ;
	tmp = ft_strdup(*s);
	i = 0;
	while (tmp[i] != '\0' && tmp[i] == 43)
		i++;
	if (i == 1)
	{
		check_free_and_null(s);
		*s = ft_strdup(tmp + 1);
		check_free_and_null(&tmp);
		return ;
	}
	check_free_and_null(&tmp);
}

static void	exit_calc(long long code, t_mini *mi)
{
	if (code >= 0)
	{
		if (code > 255)
			mi->stat->s_code = code % 256;
		else
			mi->stat->s_code = code;
	}
	else
	{
		mi->stat->s_code = code + 256;
		if (code <= -255)
			mi->stat->s_code %= (256 + 0U);
	}
}

void	b_exit(t_command *c_node, t_mini *mi)
{
	long long	code;
	int			err;
	char		*str_code;
	char		*arg;

	if (c_node->num_a == 1)
		return (exit_argless(c_node, mi));
	code = ft_atoll(c_node->args[1]);
	rm_plus_sign(&c_node->args[1]);
	str_code = ft_lltoa(code);
	arg = ft_strtrim(c_node->args[1], "     ");
	if (ft_strcmp(str_code, arg) != 0)
		err = exit_err(mi, 2, c_node);
	else
		err = exit_err(mi, 1, c_node);
	check_free_and_null(&arg);
	check_free_and_null(&str_code);
	if (err)
		return ;
	exit_calc(code, mi);
	conditional_exit_display(c_node->size);
	garbage_burner(mi);
	free_mini(mi);
	exit(mi->stat->s_code);
}
