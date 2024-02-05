/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:17:44 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/20 20:14:21 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_key(char *exported)
{
	int	i;

	i = 0;
	while (exported[i] != '\0' && exported[i] != '=')
		i++;
	return (ft_substr(exported, 0, i));
}

char	*get_fvalue(t_fixed *f_node, char *fkey)
{
	t_fixed	*ftmp;

	ftmp = f_node;
	while (ftmp != NULL)
	{
		if (!ft_strcmp(fkey, ftmp->fkey))
			return (ftmp->fvalue);
		ftmp = ftmp->fnext;
	}
	return (NULL);
}

void	update_fvalue(t_fixed **fix, char *fkey, char *fval)
{
	t_fixed	*ftmp;

	ftmp = *fix;
	while (ftmp != NULL)
	{
		if (!ft_strcmp(fkey, ftmp->fkey))
			ftmp->fvalue = fval;
		ftmp = ftmp->fnext;
	}
}

char	*get_oldpwd(t_fixed *f_node)
{
	t_fixed	*ftmp;

	ftmp = f_node;
	while (ftmp != NULL)
	{
		if (!ft_strcmp(ftmp->fkey, "OLDPWD"))
			return (ftmp->fvalue);
		ftmp = ftmp->fnext;
	}
	return (NULL);
}
