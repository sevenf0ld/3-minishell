/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:23:02 by maiman-m          #+#    #+#             */
/*   Updated: 2023/08/30 14:36:47 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	look_for_nl(char *to_search)
{
	int	i;

	if (!to_search)
		return (0);
	i = 0;
	while (to_search[i] != '\0')
	{
		if (to_search[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
