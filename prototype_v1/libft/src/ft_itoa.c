/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:19:26 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/04 18:55:49 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	validate(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

static size_t	get_length(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i += 1;
		n = validate(n);
	}
	else if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*s;
	size_t			len;
	unsigned int	num;

	len = get_length(n);
	s = malloc(len + 1);
	num = validate(n);
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (n < 0)
		s[0] = '-';
	else if (n == 0)
		s[0] = '0';
	while (num)
	{
		s[--len] = num % 10 + '0';
		num /= 10;
	}
	return (s);
}
