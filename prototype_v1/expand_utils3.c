/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:48:44 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 16:02:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ext_dollar(char *ref, int *i, int *j, char **ext)
{
	*j = *i + 1;
	while (ft_isalnum(ref[*j]) && ref[*j])
		(*j)++;
	*ext = ft_substr(ref, *i + 1, *j - *i - 1);
}

static void	exp_dollar(char *ext, char **sub)
{
        char    *tmp;

        tmp = getenv(ext);
	if (!tmp)
		*sub = ft_strdup("");
	else
		*sub = ft_strdup(tmp);
}

void    sub_exp(char **sub, char *ref)
{
	int		i;
	int		j;
	char	*ext;
	int		q[2];

	q[0] = -1;
	q[1] = -1;
	check_free_and_null(sub);
	i = 0;
        ext = NULL;
	till_dollar(ref, &i, q);
	if (ref[i] == 36)
		ext_dollar(ref, &i, &j, &ext);
	exp_dollar(ext, sub);
	check_free_and_null(&ext);
}
