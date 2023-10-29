/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:34:44 by maiman-m          #+#    #+#             */
/*   Updated: 2023/10/29 15:55:53 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
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
*/

/*
 * loop ends on INT_MIN
 * need to add error handling for dup2
 * need to add error handling for close
 */
static void	redirect_io_file(int *fd_arr, char mode, t_command *c_node)
{
	int	i;
	
	i = 0;
	while (fd_arr[i] != INT_MIN)
		i++;
	close_err(c_node->pipe_fd[0]);
	close_err(c_node->pipe_fd[1]);
	//print_inode(fd_arr[i - 1], "file");
	if (mode == 'i')
	{
		printf("i should dup2 stdin\n");
		//dup2_err(fd_arr[i - 1], STDIN_FILENO);
		//dup2(open("fake_stdin.txt", O_RDONLY), STDIN_FILENO);
		//print_inode(STDIN_FILENO, "stdin");
	}
	else if (mode == 'o')
	{
		printf("i should dup2 stdout\n");
		//dup2_err(fd_arr[i - 1], STDOUT_FILENO);
		//dup2(open("fake_stdout.txt", O_APPEND), STDOUT_FILENO);
		//print_inode(STDOUT_FILENO, "stdout");
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
			redirect_io_file(cur->std_in, 'i', cur);
		if (cur->std_out_o != NULL)
			redirect_io_file(cur->std_out_o, 'o', cur);
		if (cur->std_out_a != NULL)
			redirect_io_file(cur->std_out_a, 'o', cur);
		cur = cur->next;
	}
}
