/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:14:45 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/22 18:17:13 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**init_expandables(char *to_expand, int len, t_status *stat)
{
	t_exp_norme	exp_params;

	exp_params = (t_exp_norme){0};
	while (exp_params.i < len && to_expand[exp_params.i] != '\0')
	{
		while (exp_params.i < len && to_expand[exp_params.i] != '\0' && to_expand[exp_params.i] != '$')
			exp_params.i++;
		exp_params.j = exp_params.i + 1;
		while (exp_params.j < len && to_expand[exp_params.j] != '\0'
			&& (to_expand[exp_params.j] != '\"'
				&& to_expand[exp_params.j] != 32
				&& to_expand[exp_params.j] != '$'))
			exp_params.j++;
		exp_params.displace = ft_substr(to_expand + exp_params.i, 0, exp_params.j - exp_params.i);
		if (exp_params.displace && *exp_params.displace)
			exp_params.count += 1;
		exp_params.i += ft_strlen(exp_params.displace);
	}
	exp_params.exp = malloc_err(sizeof(char *) * (exp_params.count + 1), stat);
	exp_params.exp[exp_params.count] = NULL;
	return (exp_params.exp);
}
