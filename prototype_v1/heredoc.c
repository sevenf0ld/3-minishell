/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:35:46 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 15:57:31 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char *join_and_free(char *to_free, char *to_concat)
{
    char *end;

    end = ft_strjoin(to_free, to_concat);
    free(to_free);
    to_free = NULL;
    return (end);
}

static void    prompt_and_wait(char *delim, t_status *stat)
{
    char    *input;
    int     tmp_output;
    int     tmp_append;

    input = NULL;
    tmp_output = lim_err("tmp_lim.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777, stat);
    tmp_append = lim_err("tmp_lim.txt", O_CREAT | O_WRONLY | O_APPEND, 0666, stat);
    write(tmp_output, "", 0);
    while (1)
    {
        input = readline("mini_heredoc > ");
        if (!ft_strcmp(input, delim))
            break ;
        input = join_and_free(input, "\n");
        write(tmp_append, input, ft_strlen(input));
    }
}

void    heredoc(t_command *c_node, t_status *stat)
{
    int i;
    int     tmp_input;

    i = 0;
    //to by pass norminette assigning things in the beginning or smthn
    if (i > 0)
        tmp_input = lim_err("tmp_lim.txt", O_RDONLY, 0444, stat);
    while (i < c_node->num_l)
    {
        prompt_and_wait(c_node->lim[i], stat);
        i++;
    }
    tmp_input = lim_err("tmp_lim.txt", O_RDONLY, 0444, stat);
    dup2_err(tmp_input, STDIN_FILENO, stat);
}
