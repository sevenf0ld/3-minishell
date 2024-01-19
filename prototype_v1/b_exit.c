#include "mini.h"

void	b_exit(t_command *c_node)
{
	char		**end;
	int		n;
	long long	code;

	end = NULL;
	n = 0;
	//if (c_node->num_f == 0 && c_node->num_a == 0)
	//{
	//	c_node->stat->s_code = 0;
	//	return ;
	//}
	end = ft_split(c_node->og, ' ');
	while (end[n] != NULL)
		n++;
	code = ft_atoll(end[1]);
	if (ft_strcmp(ft_lltoa(code), end[1]) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", end[1]);
		c_node->stat->s_code = 2;
		exit(c_node->stat->s_code);
	}
	else
	{
		if (n > 2)
		{
			printf("minishell: exit: too many arguments\n");
			c_node->stat->s_code = 1;
		}
	}
	if (code >= 0)
	{
		if (code > 255)
			c_node->stat->s_code = code % 256;
		else
			c_node->stat->s_code = code;
	}
	else
	{
		c_node->stat->s_code = code + 256;
		if (code <= -255)
			c_node->stat->s_code %= (256 + 0U);
	}
        exit(c_node->stat->s_code);
}
