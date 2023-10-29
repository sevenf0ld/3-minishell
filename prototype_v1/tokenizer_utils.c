/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:19:30 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/29 15:14:14 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * | > <
 * " '
 */
int	is_delim(char a)
{
	if (a == 124 || a == 62 || a == 60)
		return (1);
	if (a == 34 || a == 39)
		return (1);
	return (0);
}

char	*handle_spaces_btwn_q(char a, char c)
{
	if (a == 34 && c == 34)
		return (ft_strdup(" "));
	if (a == 39 && c == 39)
		return (ft_strdup(" "));
	return (NULL);
}

static int	num_sbq(char *s)
{
	int	i = -1;
	int	num = 0;
	while (s[++i] != '\0')
	{
		if (ft_iswhite(s[i]))
		{
			if (s[i - 1] == 34 && s[i + 1] == 34)
				num += 1;
			if (s[i - 1] == 39 && s[i + 1] == 39)
				num += 1;
		}
	}
	return (num);
}

/*
 * counting number of quotes does not handle correctly
 * if the btwn the quotes is not space
static int	num_sbq(char *s)
{
	int	i = -1;
	int	num = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
			num += 1;
		i++
	}
}
*/

/*
 * alex's version which calculates the enclosed spaces correctly
static int	num_sbq(char *s)
{
	int	i;
	int	num;
	int	total;

	i = -1;
	num = 0;
	total = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
			num += 1;
		if (num == 2)
		{
			total += 1;
			num = 0;
		}
	}
	printf("CHECK TOTAL SBQ %i\n", total);
	return (total);
}
*/

char	**init_split_pipeline(char *s, int w_c)
{
	int		additional = 0;
	char	**end;

	additional = num_sbq(s) + w_c;
	end = malloc_err(sizeof(char *) * (additional + 1));
	return (end);
}
