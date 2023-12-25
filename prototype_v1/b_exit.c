#include "mini.h"

void	b_exit(t_command *c_node)
{
	if (c_node->num_f == 0 && c_node->num_f == 0)
	{
		c_node->stat->s_code = 0;
		return ;
	}
	long long	conv;
	//int	conv;
	if (c_node->num_f > 0)
	{
		conv = ft_atoll(c_node->flags[0]);
		//conv = ft_atoi(c_node->flags[0]);
		if (!ft_strcmp(ft_lltoa(conv), c_node->flags[0]))
		//if (!ft_strcmp(ft_itoa(conv), c_node->flags[0]))
		{
			//if (conv > 255)
			if (conv > -255)
				//c_node->stat->s_code = conv % 256;
				c_node->stat->s_code = conv + 256;
			else
			{
				//c_node->stat->s_code = conv;
				printf("check neg %lli\n", (conv + 256) % (256 + 0U));
				c_node->stat->s_code = (conv + 256) % (256 + 0U);
				printf("U: for things smaller than -255: %u (u) or %i (i)\n", -44 % (unsigned)256, -44 % (unsigned)256);
				printf("I: for things smaller than -255: %u (u) or %i (i)\n", -44 % 256, -44 % 256);
			}
			if (c_node->num_f > 1 || c_node->num_a > 0)
			{
				printf("minishell: exit: too many arguments\n");
				c_node->stat->s_code = 1;
				fprintf(stderr, "S_CODE [%d] but will not close this shell\n", c_node->stat->s_code);
				return ;
			}
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", c_node->flags[0]);
			c_node->stat->s_code = 2;
		}
		fprintf(stderr, "S_CODE [%d] will close this shell if it weren't for testing purposes\n", c_node->stat->s_code);
		return ;
	}
}
