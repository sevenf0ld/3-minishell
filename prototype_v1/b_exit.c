#include "mini.h"

static void rm_plus_sign(char **s)
{
    char    *tmp;
    int     i;

    tmp = *s;
    i = 0;
    while (tmp[i] != '\0' && tmp[i] == 43)
        i++;
    if (i == 1)
        *s = tmp + 1;
}

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
        rm_plus_sign(&c_node->args[1]);
	if (ft_strcmp(ft_lltoa(code), c_node->args[1]) != 0)
	{
                ft_putendl_fd("exit", STDOUT_FILENO);
                ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
                ft_putstr_fd(c_node->args[1], STDERR_FILENO);
                ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		mi->stat->s_code = 2;
		exit(mi->stat->s_code);
	}
	else
	{
		if (c_node->num_a > 2)
		{
                        ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
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
