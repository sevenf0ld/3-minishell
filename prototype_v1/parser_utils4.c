/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:26:39 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 16:41:52 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	count_enclosed_norme(char *s, int *i, int *count)
{
	int	q;

	if (s[*i] == 34 || s[*i] == 39)
	{
		q = *i;
		(*i)++;
		while (s[*i] != '\0' && s[*i] != s[q])
		{
			(*count)++;
			(*i)++;
		}
	}
}

/*
   if encounter sq or wq
   store the index at which the sq or wq is
   continue to iterate over the string until nul or the corresponding quote
   increase count to get the num of chars in the (outermost) quotes
*/
void	count_enclosed(char *s, int *size)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		count_enclosed_norme(s, &i, &count);
		if (s[i] != '\0')
		{
			if (s[i] != 34 && s[i] != 39)
				count++;
			i++;
		}
	}
	*size = count;
}

void	init_enclosed_extract(char **ext, int size)
{
	int	i;

	i = -1;
	*ext = malloc(sizeof(char) * (size + 1));
	if (!*ext)
		return ;
	while (++i < size)
		(*ext)[i] = '\0';
	(*ext)[size] = '\0';
}

static void	ext_enc_norme(char *s, char *ext, int *i, int *j)
{
	int	q;

	if (s[*i] == 34 || s[*i] == 39)
	{
		q = *i;
		(*i)++;
		while (s[*i] != '\0' && s[*i] != s[q])
		{
			ext[*j] = s[*i];
			(*j)++;
			(*i)++;
		}
	}
}

void	extract_enclosed(char *s, char *ext)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		ext_enc_norme(s, ext, &i, &j);
		if (s[i] != '\0')
		{
			if (s[i] != 34 && s[i] != 39)
			{
				ext[j] = s[i];
				j++;
			}
			i++;
		}
	}
}
