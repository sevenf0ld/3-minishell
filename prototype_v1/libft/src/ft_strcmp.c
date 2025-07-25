/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:08:06 by maiman-m          #+#    #+#             */
/*   Updated: 2023/06/09 18:08:08 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s, char *t)
{
	int	i;

	i = 0;
	while (s[i] == t[i] && s[i] != '\0')
		i++;
	return ((unsigned char)s[i] - (unsigned char)t[i]);
}
