/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:07:03 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/06 15:09:46 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	k = ft_strlen(src);
	if (n == 0)
		return (k);
	if (n < j)
		return (k + n);
	while (dst[j] != '\0' && j < n)
		j++;
	while (src[i] != '\0' && (i + j < n - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j < n)
		dst[j + i] = '\0';
	return (j + k);
}
