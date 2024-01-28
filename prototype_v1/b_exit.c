#include "mini.h"

void	b_exit(t_command *c_node, t_mini *mi)
{
	long long	code;

	if (c_node->num_a == 1)
	{
		mi->stat->s_code = 0;
                ft_putendl_fd("exit", STDOUT_FILENO);
                exit(mi->stat->s_code);
		return ;
	}
	code = ft_atoll(c_node->args[1]);
	if (ft_strcmp(ft_lltoa(code), c_node->args[1]) != 0)
	{
                ft_putendl_fd("exit", STDOUT_FILENO);
		printf("minishell: exit: %s: numeric argument required\n", c_node->args[1]);
		mi->stat->s_code = 2;
		exit(mi->stat->s_code);
	}
	else
	{
		if (c_node->num_a > 2)
		{
                        ft_putendl_fd("exit", STDOUT_FILENO);
			printf("minishell: exit: too many arguments\n");
			mi->stat->s_code = 1;
                        return ;
		}
	}
	if (code >= 0)
	{
		if (code > 255)
			mi->stat->s_code = code % 256;
		else
			mi->stat->s_code = code;
	}
	else
	{
		mi->stat->s_code = code + 256;
		if (code <= -255)
			mi->stat->s_code %= (256 + 0U);
	}
        ft_putendl_fd("exit", STDOUT_FILENO);
        exit(mi->stat->s_code);
}
