/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:08:38 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/24 23:09:20 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	decide_word(char c, bool *sq, bool *wq)
{
	if (c == 39 && !*sq && !*wq)
		*sq = true;
	else if (c == 34 && !*wq && !*sq)
		*wq = true;
	else if (c == 39 && *sq && !*wq)
		*sq = false;
	else if (c == 34 && *wq && !*sq)
		*wq = false;
}

char    *ext_dollar(char *s)
{
    int i;
    int j;
    
    i = 0;
    if (s[i] == 39)
        i += 1;
    while (s[i] != '\0')
    {
        if (s[i] == '$')
            break ;
        i++;
    }
    j = i + 1;
    while (s[j] != '\0')
    {
        if (s[j] == 39 || s[j] == 34 || s[j] == '$')
            break ;
        j++;
    }
    return (ft_substr(s, i, j - i));
}
