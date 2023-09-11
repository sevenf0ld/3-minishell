/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:17:19 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/06 14:18:32 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t i, size_t n)
{
	void	*ptr;

	if (n > SIZE_MAX / 2)
		return (NULL);
	ptr = malloc(i * n);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (i * n));
	return (ptr);
}
