/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 08:40:03 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/27 08:40:56 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_next_line(int fd)
{
	char		*temp;
	static char	*store;
	char		*bauxite;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	store = read_and_store(store, fd, temp);
	if (!store)
		return (NULL);
	bauxite = extract_newline(store);
	store = update_store(store);
	return (bauxite);
}

char	*read_and_store(char *store, int fd, char *buffer)
{
	ssize_t	num_bytes;

	num_bytes = 1;
	while (num_bytes > 0)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[num_bytes] = '\0';
		if (!store)
			store = ft_strdup("");
		store = join_and_free(store, buffer);
		if (look_for_nl(store))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (store);
}

char	*extract_newline(char *store)
{
	unsigned int	i;
	char			*aluminium;

	i = 0;
	if (!*store)
		return (NULL);
	while (store[i] != '\0' && store[i] != '\n')
		i++;
	aluminium = ft_substr(store, 0, i + 1);
	return (aluminium);
}

char	*update_store(char *store)
{
	unsigned int	i;
	char			*new;
	size_t			len;

	if (!look_for_nl(store))
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	i = 0;
	while (store[i] != '\0' && store[i] != '\n')
		i++;
	len = ft_strlen(store);
	new = ft_substr(store, i + 1, len);
	free(store);
	store = NULL;
	return (new);
}

int	look_for_nl(char *to_search)
{
	int	i;

	if (!to_search)
		return (0);
	i = 0;
	while (to_search[i] != '\0')
	{
		if (to_search[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
