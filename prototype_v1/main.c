/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/11/19 23:04:13 by maiman-m         ###   ########.fr       */
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
   fprintf(stderr, "╲ The inode of %s is %d\n", name, (int) info.st_ino);
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
			restore_stdin = dup_err(STDIN_FILENO);
			//print_inode(restore_stdout, "restore_stdout ->");
			//print_inode(restore_stdin, "restore_stdin ->");
			add_history(pipeline);
			lexer(pipeline, &tok);
			parser(&tok, &cmd, restore_stdout, restore_stdin);
			/*
			n_builtins(&cmd);
			if (cmd_size(cmd) > 1)
				n_builtins(&cmd->next);
			for (t_command *cur = cmd; cur != NULL; cur = cur->next)
				n_builtins(&cur);
			*/
			dup2_err(restore_stdout, STDOUT_FILENO);
			close_err(restore_stdout);
			dup2_err(restore_stdin, STDIN_FILENO);
			close_err(restore_stdin);
			//print_inode(STDOUT_FILENO, "restored SO ->");
			//print_inode(STDIN_FILENO, "restored SI ->");
		}
	}
}
