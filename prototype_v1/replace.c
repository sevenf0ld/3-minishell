/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:18:03 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/22 18:54:24 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	count_replacements(t_repl_norme *repl_params)
{
    repl_params->len_dis = ft_strlen(repl_params->displace);
    repl_params->len_sub = ft_strlen(repl_params->sub);
    repl_params->occur = -1;
    repl_params->shift = repl_params->og;
    repl_params->extracted = ft_strnstr(repl_params->shift, repl_params->displace, repl_params->len_dis);
    while (repl_params->extracted != NULL)
    {
        repl_params->occur++;
        repl_params->extracted = ft_strnstr(repl_params->shift, repl_params->displace, repl_params->len_dis);
        if (repl_params->extracted != NULL)
                repl_params->shift = repl_params->extracted + repl_params->len_dis;
    }
}

static void	replacement_str_init(t_repl_norme *repl_params)
{
    repl_params->diff = repl_params->len_sub - repl_params->len_dis;
    repl_params->ret = malloc(sizeof(char) * (repl_params->len_og + (repl_params->diff * repl_params->occur) + 1));
    repl_params->tmp = repl_params->ret;
}

static void	replace_and_shift(t_repl_norme *repl_params)
{
	while (repl_params->occur-- && repl_params->occur >= 0)
        {
            repl_params->shift = ft_strnstr(repl_params->og, repl_params->displace, repl_params->len_dis);
            repl_params->moved = repl_params->shift - repl_params->og;
            ft_strlcpy(repl_params->tmp, repl_params->og, repl_params->moved + 1);
            repl_params->tmp += repl_params->moved;
            ft_strlcpy(repl_params->tmp, repl_params->sub, repl_params->len_sub + 1);
            repl_params->tmp += repl_params->len_sub;
            repl_params->og += repl_params->moved + repl_params->len_dis;
        }
	ft_strlcpy(repl_params->tmp, repl_params->og, repl_params->len_og + 1);
}

char	*repl(char *og, char *displace, char *sub, int len_og)
{
	t_repl_norme	repl_params;

	repl_params = (t_repl_norme){0};
	repl_params.og = og;
	repl_params.displace = displace;
	repl_params.sub = sub;
	repl_params.len_og = len_og;
        count_replacements(&repl_params);
        replacement_str_init(&repl_params);
        replace_and_shift(&repl_params);
	return (repl_params.ret);
}
