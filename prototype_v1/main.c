/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/29 23:43:06 by maiman-m         ###   ########.fr       */
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

void    no_fork_b_exec(t_mini *mi, t_command *cur)
{
    t_fixed     *fix;

    fix = mi->fix;
    if (!cur->cmd || !cur->builtin)
        return ;
    if (!ft_strcmp(cur->cmd, "unset") && cur->size == 1)
        b_unset(cur, &fix, mi);
    if (!ft_strcmp(cur->cmd, "exit") && cur->size == 1)
        b_exit(cur, mi);
    if (!ft_strcmp(cur->cmd, "export") && cur->size == 1)
        b_export(cur, &fix, mi);
    if (!ft_strcmp(cur->cmd, "cd") && cur->size == 1)
        b_cd(cur, mi);
}

void    restore_io(t_mini *mi)
{
    t_restore   *res;
    t_status    *stat;

    res = mi->res;
    stat = mi->stat;
    dup2_err(res->std_out, STDOUT_FILENO, stat);
    dup2_err(res->std_in, STDIN_FILENO, stat);
}

void    execution(t_mini *mi)
{
    t_command   *cur;
    t_status    *stat;

    cur = mi->cmd;
    stat = mi->stat;
    while (cur != NULL)
    {
        if (cur->num_l > 0)
            heredoc(cur, stat);
        redirect_command_io(cur);
        //n_builtins(&cur, stat, &mi->cmd, pid);
        fork_exec(cur, mi);
        no_fork_b_exec(mi, cur);
        restore_io(mi);
        unlink("tmp_lim.txt");
        cur = cur->next;
    }
}

void    close_and_wait(t_mini *mi)
{
    int         wstat;
    pid_t       child;
    t_status    *stat;
    t_command   *last_cmd;
    (void)      last_cmd;

    last_close(&mi->pip);
    child = wait(&wstat);
    stat = mi->stat;
    last_cmd = cmd_last(mi->cmd);
    while (child > 0)
    {
        if (!last_cmd->builtin)
        {
            if (WIFEXITED(wstat))
                stat->s_code = WEXITSTATUS(wstat);
            else if (WIFSIGNALED(wstat))
                stat->s_code = WTERMSIG(wstat);
            else if (WIFSTOPPED(wstat))
                stat->s_code = WIFSTOPPED(wstat);
        }
        child = wait(&wstat);
    }
}

int	main(int argc, char **argv, char **envp)
{
	char    *pipeline;
        t_mini  mini;

	(void) argv;
        if (argc != 1)
            ft_putendl_fd("minishell does not take in arguments", STDERR_FILENO);
	pipeline = NULL;
        mini = (t_mini){0};
        mini_init_stat_res(&mini);
        mini_init_environ(&mini, envp);
        while (1)
	{
                signal(SIGQUIT, sig_qt_prnt);
                signal(SIGINT, sig_int_prnt);
		pipeline = readline("prompt> ");
		if (!pipeline)
		{
			printf("exit\n");
			exit(1);
		}
		else if (ft_strcmp(pipeline, "") && !all_whitespace(pipeline))
		{
			add_history(pipeline);
			if (lexer(pipeline, &mini))
                            continue ;
                        mini.res->std_out = dup_err(STDOUT_FILENO, mini.stat);
			mini.res->std_in = dup_err(STDIN_FILENO, mini.stat);
			parser(&mini);
                        mini_init_pid(&mini);
                        execution(&mini);
                        close_and_wait(&mini);
                } 
        }
}

/*
int    main(int argc, char **argv, char **envp)
{
        t_mini  mini;
        t_command *cmd;
        t_token *tok;

    (void) argv;
    (void) cmd;
        mini = (t_mini){0};
        mini_init_stat_res(&mini);
        mini_init_environ(&mini, envp);

    if (argc != 2)
        return (1);
    if (lexer(argv[1], &mini))
            return (1);
    tok = mini.tok; 
    char	*type[] = {"PIPE", "OUT_RE", "IN_RE", "CMD", "ARGS", "FILN", "LIM", "HD", "ADD", "ANON"};
    for (t_token *dl = tok; dl != NULL; dl = dl->next)
	    fprintf(stderr, "[%s] is a [%s]. expand? \x1b[32m%s\x1b[m\n", dl->token, type[dl->symbol], dl->exp?"true":"false");
    parser(&mini);
    cmd = mini.cmd;
    for (t_command *cur = cmd; cur != NULL; cur = cur->next)
    {
        for (int i = 0; cur->args[i]; i++)
            fprintf(stderr, "::: %s\n", cur->args[i]);
    }
}
*/
