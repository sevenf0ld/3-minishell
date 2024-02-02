/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:35:46 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 18:20:42 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	prompt_and_wait(char *delim, t_status *stat)
{
	char	*input;
	int		tmp_outre;
	int		tmp_add;

	input = NULL;
	tmp_outre = lim_err("tmp_lim.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777,
			stat);
	tmp_add = lim_err("tmp_lim.txt", O_CREAT | O_WRONLY | O_APPEND, 0666, stat);
	write(tmp_outre, "", 0);
	while (1)
	{
		input = readline("mini_heredoc > ");
		if (!ft_strcmp(input, delim))
			break ;
		input = join_and_free(input, "\n");
		write(tmp_add, input, ft_strlen(input));
                free(input);
	}
        free(input);
}

void	heredoc(t_command *c_node, t_status *stat)
{
	int	i;
	int	tmp_inre;

	i = 0;
	if (i > 0)
		tmp_inre = lim_err("tmp_lim.txt", O_RDONLY, 0444, stat);
	while (i < c_node->num_l)
	{
		prompt_and_wait(c_node->lim[i], stat);
		i++;
	}
	tmp_inre = lim_err("tmp_lim.txt", O_RDONLY, 0444, stat);
	dup2_err(tmp_inre, STDIN_FILENO, stat);
}
