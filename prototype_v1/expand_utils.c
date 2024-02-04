/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:40:45 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 17:44:50 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ini_exp(char **s, char **t, char **u)
{
	*s = NULL;
	*t = NULL;
	*u = NULL;
}

static void	reset_exp(char **s, char **t, char **u)
{
	check_free_and_null(s);
	check_free_and_null(t);
	check_free_and_null(u);
}

static void	free_and_dup(char **tokens, char *tmp)
{
	check_free_and_null(tokens);
	*tokens = ft_strdup(tmp);
	check_free_and_null(&tmp);
}

static void double_check_sub(char **bfr, char **sub, char **aft)
{
    if (all_whitespace(*sub))
    {
        if (ft_strcmp(*bfr, "\"") && ft_strcmp(*aft, "\""))
        {
            free(*sub);
            *sub = NULL;
            *sub = ft_strdup("");
        }
    }
}

void	expand_utils(char **tokens, t_mini *mi)
{
	char	*tmp;
	char	*bfr_exp;
	char	*sub;
	char	*aft_exp;

	if (!*tokens)
		return ;
	tmp = ft_strdup(*tokens);
	ini_exp(&bfr_exp, &sub, &aft_exp);
	while (contain_expandable(tmp))
	{
		set_bfr_exp(&bfr_exp, tmp);
		sub_exp(&sub, tmp, mi);
		set_aft_exp(&aft_exp, tmp);
                double_check_sub(&bfr_exp, &sub, &aft_exp);
                reform_word(&tmp, &bfr_exp, &sub, &aft_exp);
		reset_exp(&bfr_exp, &sub, &aft_exp);
	}
	if (ft_strcmp(*tokens, tmp) != 0)
		free_and_dup(tokens, tmp);
	else
		check_free_and_null(&tmp);
}
