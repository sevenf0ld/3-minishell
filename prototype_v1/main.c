/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/21 21:41:38 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
 * use an array of cmds to make it shorter
 */
bool	is_builtin(char *cmd)
{
    if (!cmd)
        return (false);
    if (!ft_strcmp(cmd, "echo"))
        return (true);
    else if (!ft_strcmp(cmd, "cd"))
        return (true);
    else if (!ft_strcmp(cmd, "pwd"))
        return (true);
    else if (!ft_strcmp(cmd, "export"))
        return (true);
    else if (!ft_strcmp(cmd, "unset"))
        return (true);
    else if (!ft_strcmp(cmd, "env"))
        return (true);
    else if (!ft_strcmp(cmd, "exit"))
        return (true);
    else
        return (false);
}

int	all_whitespace(char *s)
{
	int	i;

    i = 0;
    while (s[i] != '\0')
    {
        if (!ft_iswhite(s[i]))
            return (0);
        i++;
    }
    return (1);
}

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
static void print_inode(int fd, char *name) {
 struct stat info;
 if (fstat(fd, &info) != 0)
   fprintf(stderr,"fstat() error for %s %d: %s\n",name,fd,strerror(errno));
 else
   fprintf(stderr, "╳ The inode of %s is %d\n", name, (int) info.st_ino);
}

int	main(int argc, char **argv, char **envp)
{
        (void) print_inode;
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	t_env		*env;
	t_fixed		*fix;
	t_status	*stat;
	t_restore       *res;
	t_pid           *pid;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	env = NULL;
	fix = NULL;
        stat = NULL;
        res = NULL;
        pid = NULL;
	stat = malloc_err(sizeof(t_status), stat);
	stat->s_code = 0; //exit code
	res = malloc_err(sizeof(t_restore), stat);
	res->std_out = -1;
	res->std_in = -1;
	(void)argc;
	(void)argv;
	f_init(&fix, envp, stat);
	env_init(&env, envp, fix, stat);
	while (1)
	{

		init_sig();
		pipeline = readline("\033[32mminishell> \033[0m");
		if (!pipeline)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(1);
		}
		else if (ft_strcmp(pipeline, "") && !all_whitespace(pipeline))
		{
			add_history(pipeline);
			if (lexer(pipeline, &tok, stat))
                            continue ;
                        res->std_out = dup_err(STDOUT_FILENO, stat);
			res->std_in = dup_err(STDIN_FILENO, stat);
                        //print_inode(STDIN_FILENO, "\e[1;34minitial SI\e[m");
			//print_inode(STDOUT_FILENO, "\e[1;34minitial SO\e[m");
			t_pipe *pipes = parser(&tok, &cmd, env, stat);
                        pid = malloc_err(sizeof(t_pid), stat);
                        pid->pid_c = malloc_err(sizeof(pid_t) * cmd->size, stat);
			for (t_command *cur = cmd; cur != NULL; cur = cur->next)
			{
				if (cur->num_l > 0)
					heredoc(cur, stat);
				redirect_command_io(cur);
				signal(SIGINT, sig_int_chld);
				signal(SIGQUIT, sig_qt_chld);
                                n_builtins(&cur, stat, &cmd, pid);
                                if (!ft_strcmp(cur->cmd, "unset") && cur->size == 1)
                                    b_unset(cur, &fix);
                                if (!ft_strcmp(cur->cmd, "exit") && cur->size == 1)
                                    b_exit(cur);
                                if (!ft_strcmp(cur->cmd, "export") && cur->size == 1)
                                    b_export(cur, &fix);
                                if (!ft_strcmp(cur->cmd, "cd") && cur->size == 1)
                                    b_cd(cur);

                                //fprintf(stderr, "\x1b[32m %i \x1b[m\n", pid->pid_c[cur->pos]);

			        //print_inode(STDIN_FILENO, "\e[1;31mexec SI\e[m");
			        //print_inode(STDOUT_FILENO, "\e[1;31mexec SO\e[m");
                                dup2_err(res->std_out, STDOUT_FILENO, stat);
			        dup2_err(res->std_in, STDIN_FILENO, stat);
                                //print_inode(STDIN_FILENO, "\e[1;32mrestore SI\e[m");
				//print_inode(STDOUT_FILENO, "\e[1;32mrestore SO\e[m");
                                unlink("tmp_lim.txt");
                        }
                        last_close(&pipes);
                        int wstat = 0;
                        pid_t c = wait(&wstat);
                        while (c > 0)
                            c = wait(&wstat);
                } 
        }
}
