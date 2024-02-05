/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:58:25 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/06 15:14:14 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *ndl, size_t n)
{
	size_t	i;
	size_t	j;

	if (!*ndl)
		return ((char *)hay);
	i = 0;
	j = 0;
	while (i < n && *hay)
	{
		if (hay[i] == ndl[j])
		{
			while (hay[i + j] == ndl[j] && i + j < n)
			{
				if (ndl[j + 1] == '\0')
					return ((char *)hay + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
