/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:34:44 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/11 13:28:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static void print_inode(int fd, char *name) {
 struct stat info;
 if (fstat(fd, &info) != 0)
   fprintf(stderr,"fstat() error for %s %d: %s\n",name,fd,strerror(errno));
 else
   fprintf(stderr, "┳ The inode of %s is %d\n", name, (int) info.st_ino);
}

static void	redirect_io_file(int *fd_arr, char mode)
{
	int	i;

	i = 0;
	while (fd_arr[i] != INT_MIN)
		i++;
	if (mode == 'i')
	{
		print_inode(fd_arr[i - 1], "stdin will point to fd which");
		print_inode(STDIN_FILENO, "stdin");
		//fprintf(stderr, "pid is %d\n", getpid());
		dup2_err(fd_arr[i - 1], STDIN_FILENO);
		print_inode(STDIN_FILENO, "stdin has now become");
		//fprintf(stderr, "pid is %d\n", getpid());
	}
	else if (mode == 'o')
	{
		print_inode(fd_arr[i - 1], "stdout will point to fd which");
		print_inode(STDOUT_FILENO, "stdout");
		//fprintf(stderr, "pid is %d\n", getpid());
		dup2_err(fd_arr[i - 1], STDOUT_FILENO);
		print_inode(STDOUT_FILENO, "stdout has now become");
		//fprintf(stderr, "pid is %d\n", getpid());
	}
}

/*
 * prioritized because
 * ├ if there is any output redirection, pipe write_end[1] will be left empty
 * └ if there is any input redirection, pipe read_end[0] will be left empty
 * calls redirect_io_file() which redirects the STDIN_FILENO and STDOUT_FILENO to the last file accordingly
 */
void	handle_redirections(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	while (cur != NULL)
	{
		if (cur->std_in != NULL)
		{
			redirect_io_file(cur->std_in, 'i');
			fprintf(stderr, "%s redirects stdin to file\n", cur->cmd);
		}
		if (cur->std_out_o != NULL)
		{
			redirect_io_file(cur->std_out_o, 'o');
			fprintf(stderr, "%s redirects stdout (overwrite) to file\n", cur->cmd);
		}
		if (cur->std_out_a != NULL)
		{
			redirect_io_file(cur->std_out_a, 'o');
			fprintf(stderr, "%s redirects stdout (append) to file\n", cur->cmd);
		}
		cur = cur->next;
	}
}
