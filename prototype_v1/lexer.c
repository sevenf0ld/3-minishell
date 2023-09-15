/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:25:31 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/15 13:56:05 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * turns the words into tokens
 */
void	lexer(char *pipeline, t_token **tokens)
{
	char	delim[] = {124, 62, 60, 34, 39};
	size_t	size;
	char	**words;

	size = sizeof(delim) / sizeof(delim[0]);
	words = new_split(pipeline, delim, size);
	token_init(words, tokens);
}
