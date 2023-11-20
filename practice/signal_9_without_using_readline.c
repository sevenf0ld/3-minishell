#include "../prototype_v1/mini.h"


void sig_int(int signum)
{
	ft_putstr_fd("\b\b  \nprompt > ", STDERR_FILENO);
}

void sig_quit(int signum)
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}


int main(void)
{
	char *pipeline;
	
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);

	while (1)
	{
		ft_putstr_fd("minishell > ", STDERR_FILENO);
		pipeline = get_next_line(0);
		if (pipeline == NULL)
		{
			ft_putstr_fd("\b exit\n", STDERR_FILENO);
			return (0);
		}
		printf("%s", pipeline);
	}

	return (0);
}


// gcc signal_9_without_using_readline.c ../prototype_v1/libft/libft.a  -o signal_9_without_using_readline.out
