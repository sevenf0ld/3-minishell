/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:40:00 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/02 16:42:44 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
