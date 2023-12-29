/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2023/12/29 18:44:09 by maiman-m         ###   ########.fr       */
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
   fprintf(stderr, "╳ The inode of %s is %d\n", name, (int) info.st_ino);
}

/*
 * use an array of cmds to make it shorter
 */
bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		return (true);
	else if (ft_strcmp(cmd, "cd"))
		return (true);
	else if (ft_strcmp(cmd, "pwd"))
		return (true);
	else if (ft_strcmp(cmd, "export"))
		return (true);
	else if (ft_strcmp(cmd, "unset"))
		return (true);
	else if (ft_strcmp(cmd, "env"))
		return (true);
	else if (ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

int	all_whitespace(char *cmd)
{
    int	i;

    i = 0;
    while (cmd[i] != '\0')
    {
        if (!ft_iswhite(cmd[i]))
            return (0);
        i++;
    }
    return (1);
}

///*
int	main(int argc, char **argv, char **envp)
{
	char		*pipeline;
	t_token		*tok;
	t_command	*cmd;
	t_env		*env;
	t_fixed		*fix;
	t_status	*stat;
        t_restore       *res;

	pipeline = NULL;
	// signal(SIGINT, sig_int);
	// signal(SIGQUIT, sig_quit);
	tok = NULL;
	cmd = NULL;
	env = NULL;
	fix = NULL;
	stat = malloc_err(sizeof(t_status));
	stat->s_code = 0;
        res = malloc_err(sizeof(t_restore));
        res->std_out = -1;
        res->std_in = -1;
	(void) argc;
	(void) argv;
	f_init(&fix, envp);
	env_init(&env, envp, fix);
	while (1)
	{
		// ft_putstr_fd("minishell > ", STDERR_FILENO);
		// pipeline = get_next_line(0);
		// if (pipeline == NULL)
		// {
		// 	ft_putstr_fd("\b exit\n", STDERR_FILENO);
		// 	return (0);
		// }
		// printf("%s", pipeline);
		pipeline = readline("prompt> ");
		if (!pipeline)
		{
			printf("exit\n");
			exit(1);
		}
		else if (ft_strcmp(pipeline, "") && !all_whitespace(pipeline))
		{
			add_history(pipeline);
			lexer(pipeline, &tok, stat);
			res->std_out = dup_err(STDOUT_FILENO);
			res->std_in = dup_err(STDIN_FILENO);
			print_inode(STDIN_FILENO, "\e[1;34minitial SI\e[m");
			print_inode(STDOUT_FILENO, "\e[1;34minitial SO\e[m");
			parser(&tok, &cmd, env, stat);
			for (t_command *cur = cmd; cur != NULL; cur = cur->next)
			{
				/*
				char *count = malloc(sizeof(10));
				sprintf(count, "%s\n", ft_itoa(cur->pos));
				fprintf(stderr, "%i/%i: %s (%s)\n\twith %i flag(s) and %i arg(s)\n\twith %i in_re, %i out_re, %i add\n\tread_end %i	write_end %i\n", cur->pos, cur->size, cur->cmd, cur->builtin?"builtin":"non", cur->num_f, cur->num_a, cur->num_si, cur->num_so_o, cur->num_so_a, cur->read_end, cur->write_end);
				*/
				redirect_command_io(cur);
				/*
				if (cur->read_end != -1)
					print_inode(cur->read_end, count);
				if (cur->write_end != -1)
					print_inode(cur->write_end, count);
				*/
				/*
				if (!cur->builtin)
					n_builtins(&cur, stat);
                else if (!ft_strcmp(cur->cmd, "echo"))
					b_echo(cur);
				else if (!ft_strcmp(cur->cmd, "pwd"))
					b_pwd(cur, 'w');
				else if (!ft_strcmp(cur->cmd, "cd"))
					b_cd(cur);
				else if (!ft_strcmp(cur->cmd, "env"))
					b_env(cur, &fix);
				else if (!ft_strcmp(cur->cmd, "unset"))
					b_unset(cur, &fix);
				else if (!ft_strcmp(cur->cmd, "export"))
					b_export(cur, &fix);
				else if (!ft_strcmp(cur->cmd, "exit"))
					b_exit(cur);
				*/
				///*
				print_inode(STDIN_FILENO, "\e[1;31mexec SI\e[m");
				print_inode(STDOUT_FILENO, "\e[1;31mexec SO\e[m");
				//*/
				
				dup2_err(res->std_out, STDOUT_FILENO);
				//close_err(res->std_out);
				dup2_err(res->std_in, STDIN_FILENO);
				//close_err(res->std_in);
				
				///*
				print_inode(STDIN_FILENO, "\e[1;32mrestore SI\e[m");
				print_inode(STDOUT_FILENO, "\e[1;32mrestore SO\e[m");
				//*/
				}
				/*
				dup2_err(res->std_out, STDOUT_FILENO);
				close_err(res->std_out);
				dup2_err(res->std_in, STDIN_FILENO);
				close_err(res->std_in);
				*/
			}
		}
	}
	//*/

/*
int	main(int argc, char **argv)
{
	t_token		*tok;
	t_command	*cmd;
	t_env		*env;
	t_status	*stat;
	tok = NULL;
	cmd = NULL;
	env = NULL;
	stat = malloc_err(sizeof(t_status));
	stat->s_code = 0;
	char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
	if (argc != 2)
		return (1);
	lexer(argv[1], &tok, stat);
	for (t_token *dl = tok; dl != NULL; dl = dl->next)
		printf("[%s] is a [%s]. expand? \x1b[32m%s\x1b[m\n", dl->token, type[dl->symbol], dl->exp?"true":"false");
	parser(&tok, &cmd, env, stat);
	t_command *tmp;
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
	{
		printf("@ [%s]\n", tmp->cmd);
		if (tmp->flags != NULL)
		{
			for (int i = 0; i < tmp->num_f; i++)
				printf("--- {%s}\n", tmp->flags[i]);
		}
		if (tmp->args != NULL)
		{
			for (int i = 0; i < tmp->num_a; i++)
				printf("::: {%s}\n", tmp->args[i]);
		}
	}
}
*/
