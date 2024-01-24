/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:08:55 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/24 21:59:28 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	e_k_params_helper(t_exp_key_norme *e_k_params, char *to_expand, int len)
{
	while (e_k_params->i < len && to_expand[e_k_params->i] != '\0'
		&& to_expand[e_k_params->i] != '$')
		e_k_params->i++;
	e_k_params->j = e_k_params->i + 1;
	while (e_k_params->j < len && to_expand[e_k_params->j] != '\0'
		&& (to_expand[e_k_params->j] != '\"'
			&& to_expand[e_k_params->j] != 32
			&& to_expand[e_k_params->j] != '$')
			&& to_expand[e_k_params->j] != 39)
		e_k_params->j++;
}

char	**get_exp_key(char *to_expand, int len, t_status *stat)
{
	t_exp_key_norme	e_k_params;	

	e_k_params = (t_exp_key_norme){0};
	e_k_params.exp = init_expandables(to_expand, len, stat);
	while (e_k_params.i < len && to_expand[e_k_params.i] != '\0')
	{
		e_k_params_helper(&e_k_params, to_expand, len);
		e_k_params.displace = ft_substr(to_expand + e_k_params.i, 0, e_k_params.j - e_k_params.i);
		e_k_params.len_dis = ft_strlen(e_k_params.displace);
		if (e_k_params.displace && *e_k_params.displace)
		{
			if (e_k_params.displace[e_k_params.len_dis - 1] == 39)
				e_k_params.displace = ft_strndup(e_k_params.displace, e_k_params.len_dis - 1);
			e_k_params.exp[e_k_params.k++] = e_k_params.displace;
		}
		e_k_params.i += e_k_params.len_dis;
	}
	return (e_k_params.exp);
}

char	**get_exp_value(char *to_expand, int len, t_status *stat, char **key)
{
	int		i;
	char	*sub;
	char	**exp;

	i = 0;
	sub = NULL;
	exp = init_expandables(to_expand, len, stat);
	while (key[i] != NULL)
	{
		sub = getenv(key[i] + 1);
		if (sub != NULL)
			exp[i] = sub;
		else
			exp[i] = "";
		i++;
	}
	return (exp);
}

char	*sub_exp(char *s, int len, char **key, char **val)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (key[i] != NULL)
	{
		ret = repl(s, key[i], val[i], len);
		if (ret != NULL)
		{
			s = ret;
			len = ft_strlen(s);
		}
		i++;
	}
	return (ret);
}
