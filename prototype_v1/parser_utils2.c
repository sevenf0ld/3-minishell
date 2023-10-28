/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:34:44 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/28 16:15:43 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void print_inode(int fd, char *name) {
 struct stat info;
 if (fstat(fd, &info) != 0)
   fprintf(stderr,"fstat() error for %s %d: %s\n",name,fd,strerror(errno));
 else
   fprintf(stderr, "The inode of %s %d is %d\n", name, fd, (int) info.st_ino);
}

/*
 * loop ends on INT_MIN
 * need to add error handling for dup2
 */
void	redirect_io_file(int *fd_arr, char mode)
{
	int	i;
	
	i = 0;
	while (fd_arr[i] != INT_MIN)
		i++;
	print_inode(fd_arr[i - 1], "file");
	if (mode == 'i')
	{
		//printf("i should dup2 stdin\n");
		dup2(fd_arr[i - 1], STDIN_FILENO);
		print_inode(STDIN_FILENO, "stdin");
	}
	else if (mode == 'o')
	{
		//printf("i should dup2 stdout\n");
		dup2(fd_arr[i - 1], STDOUT_FILENO);
		print_inode(STDOUT_FILENO, "stdout");
	}
}

/*
 * if size is one means there is no pipe
 * 		redir only involves files if any
 * if not NULL means there is a redirection
 * 		iterate until before INT_MIN and dup2 STDIN/STDOUT_FILENO
 * 		make a distinction between out_re and add?
 */
void	handle_redirections(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->std_in != NULL)
			redirect_io_file(cur->std_in, 'i');
		if (cur->std_out_o != NULL)
			redirect_io_file(cur->std_out_o, 'o');
		if (cur->std_out_a != NULL)
			redirect_io_file(cur->std_out_a, 'o');
		cur = cur->next;
	}
}
