/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:26:35 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/20 05:34:50 by maiman-m         ###   ########.fr       */
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
   fprintf(stderr, "┰ The inode of %s is %d\n", name, (int) info.st_ino);
}

void	redirect_io_file(int *fd_arr, char mode)
{
	int	i;

	i = 0;
	while (fd_arr[i] != INT_MIN)
		i++;
	if (mode == 'i')
	{
		dup2_err(fd_arr[i - 1], STDIN_FILENO);
		print_inode(STDIN_FILENO, "stdin redirected to file");
	}
	else if (mode == 'o')
	{
		dup2_err(fd_arr[i - 1], STDOUT_FILENO);
		print_inode(STDOUT_FILENO, "stdout redirected to file");
	}
}

/*
 * if FIRST
 * ├ read from SI
 * └ write to pipe write_end[1]
 *
 * if LAST
 * ├ read from pipe read_end[0]
 * └ write to SO
 *
 * if IN BETWEEN
 * ├ read from pipe read_end[0]
 * └ write to pipe write_end[1]
 */
void	redirect_io_pipe(t_command *c_node)
{
	t_command	*cur;

	cur = c_node;
	if (!cur)
		return ;
	if (cur->pos == 0)
	{
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
		{
			/*
			fprintf(stderr, "1. THE CMD is %s\n", cur->cmd);
			print_inode(STDIN_FILENO, "first stdin before closing read end");
			print_inode(cur->read_end, "first read end before closing");
			close_err(cur->read_end);
			dup2_err(cur->write_end, STDOUT_FILENO);
			print_inode(cur->write_end, "first write end");
			print_inode(STDOUT_FILENO, "first stdout");
			close_err(STDOUT_FILENO);
			close_err(cur->write_end);
			*/
			//close_err(cur->read_end); //grep: (standard input): Bad file descriptor
			dup2_err(cur->write_end, STDOUT_FILENO);
		}
	}
	else if (cur->pos == cur->size - 1)
	{
		if (cur->std_in == NULL)
		{
			/*
			fprintf(stderr, "N. THE CMD is %s\n", cur->cmd);
			print_inode(STDOUT_FILENO, "last stdout before closing write end");
			print_inode(cur->write_end, "last write end before closing");
			close_err(cur->write_end);
			dup2_err(cur->read_end, STDIN_FILENO);
			print_inode(cur->read_end, "last read end");
			print_inode(STDIN_FILENO, "last stdin");
			close_err(STDIN_FILENO);
			close_err(cur->read_end);
			*/
			print_inode(cur->read_end, "last read end");
			print_inode(STDIN_FILENO, "last stdin");
			//dup2_err(cur->read_end, STDIN_FILENO);
			dup2_err(cur->read_end, STDOUT_FILENO);
			print_inode(cur->read_end, "last read end");
			print_inode(STDIN_FILENO, "last stdin");
			close_err(STDIN_FILENO);
		}
	}
	else
	{
		if (cur->std_in == NULL)
			dup2_err(cur->read_end, STDIN_FILENO);
		if (cur->std_out_o == NULL && cur->std_out_a == NULL)
			dup2_err(cur->write_end, STDOUT_FILENO);
		print_inode(cur->read_end, "in btwn read end");
		print_inode(cur->write_end, "in btwn write end");
	}
}

/*
 * if NULL means no file redirection
 * 		read from pipe read_end[0]
 * 		write to pipe write_end[1]
 * else read from or write to file
 */
void	redirect_command_io(t_command *c_node)
//void	redirect_command_io(t_command *c_node, int ro, int ri)
{
	t_command	*cur;

	cur = c_node;
	if (!cur)
		return ;
	fprintf(stderr, "───────────────────────────────FILE BEFORE───────────────────────────────\n");
	print_inode(STDIN_FILENO, "stdin before in_re");
	print_inode(STDOUT_FILENO, "stdout before out_re");
	fprintf(stderr, "───────────────────────────────FILE BEFORE───────────────────────────────\n");
	if (cur->std_in != NULL)
		redirect_io_file(cur->std_in, 'i');
	//if (cur->std_out_o != NULL)
	if (cur->std_out_o != NULL || cur->std_out_a != NULL)
		redirect_io_file(cur->std_out_o, 'o');
	//if (cur->std_out_a != NULL)
		//redirect_io_file(cur->std_out_a, 'o');
	fprintf(stderr, "─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─FILE AFTER─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─\n");
	print_inode(STDIN_FILENO, "stdin after in_re");
	print_inode(STDOUT_FILENO, "stdout after out_re");
	fprintf(stderr, "─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─FILE AFTER─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─\n");
	if (cur->size == 1)
		return ;
	/*
	dup2_err(ro, STDOUT_FILENO);
	dup2_err(ri, STDIN_FILENO);
	*/
	redirect_io_pipe(cur);
	/*
	dup2_err(ro, STDOUT_FILENO);
	dup2_err(ri, STDIN_FILENO);
	*/
	/*
	print_inode(STDIN_FILENO, "stdin after in_re");
	print_inode(STDOUT_FILENO, "stdout after out_re");
	*/
	/*
	if (cur->std_in == NULL)
		redirect_io_pipe(cur);
	if (cur->std_out_o == NULL || cur->std_out_a == NULL)
		redirect_io_pipe(cur);
	//if (cur->std_out_a == NULL)
		//redirect_io_pipe(cur);
	*/
}
