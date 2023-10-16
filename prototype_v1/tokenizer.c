/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:59 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/16 15:47:18 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	w_c(char *s)
{
	int	i;
	int	count;
	int	reset;

	i = 0;
	count = 0;
	reset = 0;
	while (s[i] != '\0')
	{
		if (is_delim(s[i]))
			count += 1;
		else if (!ft_iswhite(s[i]) && reset == 0 && !is_delim(s[i]))
		{
			count += 1;
			reset = 1;
		}
		else if (ft_iswhite(s[i]))
			reset = 0;
		i++;
	}
	return (count);
}

static char	*assign_delim(char *s, char a)
{
	s = malloc(sizeof(char) + 1);
	s[0] = a;
	s[1] = '\0';
	printf("ASSIGN DELIM %s\n", s);
	return (s);
}

static int	w_l(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !ft_iswhite(s[i]) && !is_delim(s[i]))
		i++;
	return (i);
}

/*
 * breaks the command and arguments into words based on
 * | > < “ ‘ space ( ) &
 * 124 62 60 34 39 32 40 41 38
 */
char	**new_split(char *str)
{
	int		i;
	int		j;
	int		count;
	char	**end;
	char	*sp_w_q;
	int		num;

	i = -1;
	j = 0;
	count = w_c(str);
	printf("WORD COUNT BEFORE SPLIT %i\n", count);
	//to handle echo " " or echo ' '
	//end = malloc(sizeof(char *) * (count + 2));
	end = init_split_pipeline(str, w_c(str));
	sp_w_q = NULL;
	num = 0;
	while (str[++i] != '\0')
	{
		if (!ft_iswhite(str[i]))
		{
			if (is_delim(str[i]))
			{
				if ((str[i] == 39 || str[i] == 34))
				{
					num += 1;
					if (num == 2)
					{
						end[j] = assign_delim(end[j], str[i]);
						num = 0;
					}
					/*
					num += 1;
					printf("bullshit :D, %d\n", num);
					*/
				}
				else
					end[j] = assign_delim(end[j], str[i]);
			}
			else
			{
				end[j] = ft_strndup(str + i, w_l(str + i));
				i = i - 1 + w_l(str + i);
			}
			j += 1;
		}
		else
		{
			sp_w_q = handle_spaces_btwn_q(str[i - 1], str[i + 1]);
			if (sp_w_q != NULL)
				end[j++] = sp_w_q;
		}
	}
	end[j] = NULL;
	return (end);
}
