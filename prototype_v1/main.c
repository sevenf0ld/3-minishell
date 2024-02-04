/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:19:04 by maiman-m          #+#    #+#             */
/*   Updated: 2024/02/04 20:26:42 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	execution(t_mini *mi)
{
	t_command	*cur;
	t_status	*stat;

	cur = mi->cmd;
	stat = mi->stat;
	while (cur != NULL)
	{
		if (cur->num_l > 0)
			heredoc(cur, stat);
		redirect_command_io(cur);
		fork_exec(cur, mi);
		no_fork_b_exec(mi, cur);
		restore_io(mi);
		unlink("tmp_lim.txt");
		cur = cur->next;
	}
}

void	minishell(t_mini *mini, int flag)
{
	if (flag == 0)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (flag == 1)
	{
		add_history(mini->pipeline);
		if (lexer(mini->pipeline, mini))
			return ;
		save_io(mini);
                mini->tok_cpy = mini->tok;
		// free_ttkn(mini->tok_cpy);
		parser(mini);
		mini_init_pid(mini);
		execution(mini);
		close_and_wait(mini);
		garbage_burner(mini);
	}
	else if (flag == 2)
		mini->stat->s_code = 0;
}

t_sig	g_sig;

int	main(int argc, char **argv, char **envp)
{
	char	*pipeline;
	t_mini	mini;

	(void)argv;
	if (argc != 1)
		ft_putendl_fd("minishell does not take in arguments", STDERR_FILENO);
	pipeline = NULL;
	mini = (t_mini){0};
	mini_init_stat_res(&mini);
	mini_init_environ(&mini, envp);
	while (1)
	{
		g_sig = (t_sig){0};
		signal_parent();
		pipeline = readline("prompt> ");
                mini_init_pipeline(&mini, pipeline);
		if (g_sig.sig)
			mini.stat->s_code = g_sig.sig_code;
		if (!pipeline)
			minishell(&mini, 0);
		else if (ft_strcmp(mini.pipeline, "") && !all_whitespace(pipeline))
			minishell(&mini, 1);
                /*
		else
			minishell(pipeline, &mini, 2);
                */
	}
	// free_stat(mini.stat);
	// free_res(mini.res);
	free_fix(&mini.fix);
	// free_env(&mini.env);
}
