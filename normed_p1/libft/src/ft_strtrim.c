/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:32:31 by maiman-m          #+#    #+#             */
/*   Updated: 2023/05/06 15:17:21 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	validate(char a, char const *to_trim)
{
	int	i;

	i = 0;
	if (a == '\0')
		return (1);
	i = 0;
	while (to_trim[i] != '\0')
	{
		if (to_trim[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (s1[i] != '\0')
	{
		if (!validate(s1[i], set))
			break ;
		i++;
	}
	while (j >= i)
	{
		if (!validate(s1[j], set))
			break ;
		j--;
	}
	j = j + 1 - i;
	return (ft_substr(s1, i, j));
}
