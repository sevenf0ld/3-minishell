/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/19 16:22:22 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// int hrdc(char *pipeline)
// {
// 	int	i;
// 	int kw;

// 	i = 1;
// 	while (pipeline[++i])
// 	{
// 		if (pipeline[i + 1] == '<' && pipeline[i] == '<')
// 		{
// 			printf("Contain <<\n");

// 		}
// 	}
// 	printf("Doesn't contain\n");
// 	return (0);
// }


/*
	Global Sturct for Signal Handling
*/
t_sig	g_sig;


/*
 * use an array of cmds to make it shorter
 */
bool	is_builtin(char *cmd)
{
    if (!cmd)
        return (false);
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

static int	all_whitespace(char *cmd)
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
	t_restore	*res;

	pipeline = NULL;
	tok = NULL;
	cmd = NULL;
	env = NULL;
	fix = NULL;
	stat = NULL;
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

		// printf(">g_sig.sigva_1 = %d\n", g_sig.sigva_1);
		init_sig();
		// if (g_sig.sigva_1 == 1)
		// {
		// 	// printf("a\n"); 
		// 	pipeline = readline("S");
		// 	g_sig.sigva_1 = 2;
		// }
		// else
			pipeline = readline("prompt> ");

		// hrdc(pipeline);
		pipeline = readline("prompt> ");
		if (!pipeline)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			// ft_putstr_fd("\b\rbl\n", STDOUT_FILENO);
			// rl_replace_line("prompt> exit", STDIN_FILENO);
			// rl_redisplay();
        	// rl_on_new_line();
        	// rl_redisplay();
			exit(1);
		}
		else if (ft_strcmp(pipeline, "") && !all_whitespace(pipeline))
		{
			add_history(pipeline);
			if (lexer(pipeline, &tok, stat))
                            return (1);
                        res->std_out = dup_err(STDOUT_FILENO, stat);
			res->std_in = dup_err(STDIN_FILENO, stat);
			parser(&tok, &cmd, env, stat);
			for (t_command *cur = cmd; cur != NULL; cur = cur->next)
			{
				redirect_command_io(cur);
				signal(SIGINT, sig_int_chld);
				signal(SIGQUIT, sig_qt_chld);
				if (cur->num_l > 0)
					heredoc(cur, stat);
				n_builtins(&cur, stat);
				if (!ft_strcmp(cur->cmd, "unset") && cur->size == 1)
					b_unset(cur, &fix);
				if (!ft_strcmp(cur->cmd, "exit") && cur->size == 1)
					b_exit(cur);
				dup2_err(res->std_out, STDOUT_FILENO, stat);
				dup2_err(res->std_in, STDIN_FILENO, stat);
				unlink("tmp_lim.txt");
			}
		}
		// printf(">>g_sig.sigva_1 = %d\n", g_sig.sigva_1);
    	// printf("sigint_child = %d\n", g_sig.sigint_child);
	}
}
