/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/05 18:37:33 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
        stat = NULL;
	stat = malloc_err(sizeof(t_status), stat);
	stat->s_code = 0;
        res = malloc_err(sizeof(t_restore), stat);
        res->std_out = -1;
        res->std_in = -1;
	(void) argc;
	(void) argv;
	f_init(&fix, envp, stat);
	env_init(&env, envp, fix, stat);
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
			res->std_out = dup_err(STDOUT_FILENO, stat);
			res->std_in = dup_err(STDIN_FILENO, stat);
			parser(&tok, &cmd, env, stat);
			for (t_command *cur = cmd; cur != NULL; cur = cur->next)
			{
				redirect_command_io(cur);
                                n_builtins(&cur, stat);
                                if (!ft_strcmp(cur->cmd, "unset") && cur->size == 1)
                                    b_unset(cur, &fix);
                                if (!ft_strcmp(cur->cmd, "exit") && cur->size == 1)
                                    b_exit(cur);
				dup2_err(res->std_out, STDOUT_FILENO, stat);
			        dup2_err(res->std_in, STDIN_FILENO, stat);
			}
		}
	}
}

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
        stat = NULL;
	stat = malloc_err(sizeof(t_status), stat);
	stat->s_code = 0;
	//char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "W_Q", "S_Q", "CMD", "OPT", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
	if (argc != 2)
		return (1);
	lexer(argv[1], &tok, stat);
        int std_out = dup_err(STDOUT_FILENO, stat);
        int std_in = dup_err(STDIN_FILENO, stat);
	//for (t_token *dl = tok; dl != NULL; dl = dl->next)
	//	fprintf(stderr, "[%s] is a [%s]. expand? \x1b[32m%s\x1b[m\n", dl->token, type[dl->symbol], dl->exp?"true":"false");
	parser(&tok, &cmd, env, stat);
	t_command *tmp;
	for (tmp = cmd; tmp != NULL; tmp = tmp->next)
	{
		redirect_command_io(tmp);
		fprintf(stderr, "@ [%s]\n", tmp->cmd);
		if (tmp->flags != NULL)
		{
			for (int i = 0; i < tmp->num_f; i++)
				fprintf(stderr, "--- {%s}\n", tmp->flags[i]);
		}
		if (tmp->args != NULL)
		{
			for (int i = 0; i < tmp->num_a; i++)
				fprintf(stderr, "::: {%s}\n", tmp->args[i]);
		}
                fprintf(stderr, "should be executed. \x1b[35m%s\x1b[m\n", tmp->exec?"true":"false");
                dup2_err(std_out, STDOUT_FILENO, stat);
                dup2_err(std_in, STDIN_FILENO, stat);
	}
}
*/
