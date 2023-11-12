/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/11 13:27:57 by maiman-m         ###   ########.fr       */
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
   fprintf(stderr, "┏ The inode of %s is %d\n", name, (int) info.st_ino);
}

int	main(void)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	int			restore_stdout;
	int			restore_stdin;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	while (1)
	{
		pipeline = readline("prompt> ");
		if (ft_strcmp(pipeline, ""))
		{
			restore_stdout = dup_err(STDOUT_FILENO);
			print_inode(STDOUT_FILENO, "stdout when saved");
			//fprintf(stderr, "pid is %d\n", getpid());
			restore_stdin = dup_err(STDIN_FILENO);
			print_inode(STDIN_FILENO, "stdin when saved");
			//fprintf(stderr, "pid is %d\n", getpid());
			add_history(pipeline);
			lexer(pipeline, &tok);
			parser(&tok, &cmd);
			n_builtins(&cmd);
			if (cmd_size(cmd) > 1)
				n_builtins(&cmd->next);
			dup2_err(restore_stdout, STDOUT_FILENO);
			print_inode(STDOUT_FILENO, "stdout after restoring");
			//fprintf(stderr, "pid is %d\n", getpid());
			close_err(restore_stdout);
			dup2_err(restore_stdin, STDIN_FILENO);
			print_inode(STDIN_FILENO, "stdin after restoring");
			//fprintf(stderr, "pid is %d\n", getpid());
			close_err(restore_stdin);
		}
	}
}
