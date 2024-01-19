/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/20 06:06:49 by maiman-m         ###   ########.fr       */
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
		pipeline = readline("prompt> ");
		if (!pipeline)
		{
			printf("exit\n");
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
                                if (cur->num_l > 0)
                                    heredoc(cur, stat);
				redirect_command_io(cur);
                                n_builtins(&cur, stat);
                                if (!ft_strcmp(cur->cmd, "unset") && cur->size == 1)
                                    b_unset(cur, &fix);
                                if (!ft_strcmp(cur->cmd, "exit") && cur->size == 1)
                                    b_exit(cur);
                                if (!ft_strcmp(cur->cmd, "export") && cur->size == 1)
                                    b_export(cur, &fix);
				dup2_err(res->std_out, STDOUT_FILENO, stat);
			        dup2_err(res->std_in, STDIN_FILENO, stat);
                                unlink("tmp_lim.txt");
			}
                    }
        }
}
