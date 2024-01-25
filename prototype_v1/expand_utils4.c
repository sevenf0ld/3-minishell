/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 02:21:35 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
// -----------------------------------------//
//      LOCAL-STATIC                        //
// -----------------------------------------//
int ecd_helper(char *str, int *i, int *j, int *in_quote)
{
    if (str[*i] == 39)
        in_quote[1] *= -1;
    if (str[*i] == 39
        && str[*i + 1] 
        && str[*i + 1] != str[*i]
        && in_quote[0] != 1
        && in_quote[1] == 1)
    {
        *j = *i + 1;
        while (str[*j] != str[*i] && str[*j])
            (*j)++;
        if (str[*j] == str[*i])
        {
            *i = *j;
            in_quote[1] *= -1;
        }
        if (str[*j] == '\0')
            return (1);
    }
    return (0);
}

// ascii 36 = '$', 39 = single_quote, 34 = double_quote
// in_quote[0] = double_quote, in_quote[1] = single_quote
int eu_contain_dollar(char  *str)
{
    int i;
    int j;
    int in_quote[2];

    if (str == NULL)
        return (0);
    i = 0;
    in_quote[0] = -1;
    in_quote[1] = -1;
    while (str[i] != '\0')
    {
        if (str[i] == 34)
           in_quote[0] *= -1; 
        if (ecd_helper(str, &i, &j, in_quote))
            break ;
        if (str[i] == 36 && str[i + 1] && ft_isalnum(str[i + 1]))
            return (1);
        if (str[i] != '\0')
            i++;
    }
    return (0);
}

// -----------------------------------------//
//      MAIN                                //
// -----------------------------------------//
void    expand_utils(char *str)
{
    printf("RESULT %i\n", eu_contain_dollar(str));
    /*
    char    *holder;
    char    *hd_front;
    char    *hd_expand;
    char    *hd_back;

    if (str == NULL)
        return ;
    holder = ft_strdup(str);
    while (eu_contain_dollar(holder))
    {
        eu_set_front(hd_front);
        eu_set_expand(hd_expand);
        eu_set_back(hd_back);
        holder = eu_multi_join(hd_front, hd_expand, hd_back);
    }
    if (ft_strcmp(str, holder) != 0)
        free_and_dup(str, holder);
    if (holder || hd_front || hd_expand || hd_back)
        free_holders(holder, hd_front, hd_expand, hd_back);
    */
}
