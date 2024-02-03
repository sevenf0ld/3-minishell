/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:31:13 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/03 10:37:07 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void delete_all_element(t_token **lst, char *value)
{
    if (*lst == NULL)
    {
        //count = printf("List is empty\n");
        return;
    }
    //while ((*lst)->x == value)
    while (!ft_strcmp((*lst)->token, value))
    {
        t_token *to_remove;
        to_remove = (*lst);
        //count = printf("Element '%d' is deleted.\n", (*lst)->x);
        *lst = (*lst)->next;
        free(to_remove);
    }
    t_token *curr;
    curr = *lst;
    while (curr->next != NULL)
    {
        //while (curr->next->x == value)
        while (!ft_strcmp(curr->next->token, value))
        {
            t_token *to_remove1;
            to_remove1 = curr->next;
            //count = printf("Element '%d' is deleted.\n", curr->next->x);
            curr->next = curr->next->next;
            if (curr->next == NULL)
            {
                free(to_remove1);
                return;
            }
            free(to_remove1);
        }
        curr = curr->next;
    }
    /*
    if (count == 0)
        printf("Element '%d' not found\n", value);
    */
}
