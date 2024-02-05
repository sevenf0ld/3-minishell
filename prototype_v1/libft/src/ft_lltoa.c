/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:33:53 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/20 10:37:28 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	validate(long long n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

static size_t	get_length(long long n)
{
	long long	i;

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

char	*ft_lltoa(long long n)
{
	char				*s;
	size_t				len;
	unsigned long long	num;

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
