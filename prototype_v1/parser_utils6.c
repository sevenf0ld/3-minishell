/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:40:00 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/05 10:07:46 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	remove_quotes(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		if (contain_quotes(args[i]))
			rm(args, i);
		i++;
	}
}

void	rm(char **args, int n)
{
	int		size;
	char	*ext;

	size = 0;
	count_enclosed(args[n], &size);
	enclosed_extract_init(&ext, size);
	extract_enclosed(args[n], ext);
	if (args[n] != NULL)
		check_free_and_null(&args[n]);
	args[n] = ext;
}
