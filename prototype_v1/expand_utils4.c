/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:34:58 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/26 12:04:19 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
/*
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

static void ini_holders(char **h1, char **h2, char **h3)
{
    *h1 = NULL;
    *h2 = NULL;
    *h3 = NULL;
}

static void check_free_and_null(char **str)
{
    if (*str != NULL)
    {
        free(*str);
        *str = NULL;
    }
}

static void eu_set_front(char **hd_front, char *str)
{
    int i;

    //check_free_and_null(hd_front);
    i = 0;
    while (str[i] != 36 && str[i])
        i++;
    if (str[i] == 36)
        *hd_front = ft_strndup(str, i - 1);
}

static void se_insert_expandable(char *str, int *i, int *j, char **holder)
{
   *j = *i + 1;
   while (ft_isalnum(str[*j]) && str[*j])
       (*j)++;
   *holder = ft_substr(str, *i + 1, *j);
}

static void se_insert_converted_exp(char *src, char **dst)
{
    *dst = getenv(src);
    if (!*dst)
        *dst = "";
    fprintf(stderr, "{%s: %s}\n", src, *dst);
}

static void eu_set_expand(char **hd_expand, char *str)
{
    int     i;
    int     j;
    char    *holder;

    //check_free_and_null(hd_expand);
    i = 0;
    while (str[i] != 36 && str[i])
        i++;
    if (str[i] == 36)
        se_insert_expandable(str, &i, &j, &holder);
    se_insert_converted_exp(holder, hd_expand); 
    //check_free_and_null(&holder);
}

static void eu_set_back(char **hd_back, char *str)
{
    int i;

    //check_free_and_null(hd_back);
    i = 0;
    while (str[i] != 36 && str[i])
        i++;
    if (str[i] == 36)
    {
        i++;
        while (ft_isalnum(str[i] && str[i]))
            i++;
        *hd_back = ft_substr(str, i, strlen(str) - 1);
    }
}

static void mj_join_and_free(char **holder, char **new)
{
    char    *tmp;

    tmp = strdup(*holder);
    //check_free_and_null(holder);
    *holder = ft_strjoin(tmp, *new);
    //check_free_and_null(&tmp);
}

static void eu_multi_join(char **s0, char **s1, char **s2, char **s3)
{
    fprintf(stderr, "FRONT %s\nEXPAND %s\nBACK %s\n", *s1, *s2, *s3);
    char    *holder;

    holder = strdup("");
    mj_join_and_free(&holder, s1);
    mj_join_and_free(&holder, s2);
    mj_join_and_free(&holder, s3);
    //check_free_and_null(s0);
    *s0 = strdup(holder);
    //check_free_and_null(&holder);
}

static void free_and_dup(char **str, char *holder)
{
    //check_free_and_null(str);
    *str = strdup(holder);
}

static void free_holders(char **h1, char **h2, char **h3, char **h4)
{
    check_free_and_null(h1);
    check_free_and_null(h2);
    check_free_and_null(h3);
    check_free_and_null(h4);
}
*/

// -----------------------------------------//
//      MAIN                                //
// -----------------------------------------//
void    expand_utils(char **str)
{
    (void) str;
    /*
    char    *holder;
    char    *hd_front;
    char    *hd_expand;
    char    *hd_back;

    if (*str == NULL)
        return ;
    holder = strdup(*str);
    ini_holders(&hd_front, &hd_expand, &hd_back);
    while (eu_contain_dollar(holder))
    {
        eu_set_front(&hd_front, holder);
        eu_set_expand(&hd_expand, holder);
        eu_set_back(&hd_back, holder);
        eu_multi_join(&holder, &hd_front, &hd_expand, &hd_back);
    }
    if (strcmp(*str, holder) != 0)
        free_and_dup(str, holder);
    //free_holders(&holder, &hd_front, &hd_expand, &hd_back);
    (void) free_holders;
    */
}
