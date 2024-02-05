/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:40:45 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 09:50:09 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	exp_init(char **bfr, char **sub, char **aft)
{
	*bfr = NULL;
	*sub = NULL;
	*aft = NULL;
}

static void	reset_exp(char **bfr, char **sub, char **aft)
{
	check_free_and_null(bfr);
	check_free_and_null(sub);
	check_free_and_null(aft);
}

static void	free_and_dup(char **tokens, char *tmp)
{
	check_free_and_null(tokens);
	*tokens = ft_strdup(tmp);
	check_free_and_null(&tmp);
}

static void	double_check_sub(char **bfr, char **sub, char **aft)
{
	if (all_whitespace(*sub))
	{
		if (ft_strcmp(*bfr, "\"") && ft_strcmp(*aft, "\""))
		{
			check_free_and_null(sub);
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
	exp_init(&bfr_exp, &sub, &aft_exp);
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
