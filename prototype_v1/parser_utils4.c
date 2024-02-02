/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:26:39 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/31 14:08:19 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	init_enclosed_extract(char **ext, int size)
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
static void	count_enclosed(char *s, int *size)
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

static void	extract_enclosed(char *s, char *ext)
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

//static void	rm(char **args, int n)
void	rm(char **args, int n)
{
	int		size;
	char	*ext;

	size = 0;
	count_enclosed(args[n], &size);
	init_enclosed_extract(&ext, size);
	extract_enclosed(args[n], ext);
	if (args[n] != NULL)
		free(args[n]);
	args[n] = ext;
}

//static int	contain_quotes(char *s)
int	contain_quotes(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	remove_quotes(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		if (contain_quotes(args[i]))
			rm(args, i);
		i++;
	}
}
