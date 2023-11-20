#include <signal.h>
#include <stdio.h>

typedef void	(*t_sighandler)(int);

void	customHandler(int signum)
{
	printf("Custom handler for signal %d\n", signum);
}

int	main(void)
{
	t_sighandler	previoushandler;

	// Set a custom signal handler for SIGINT (Ctrl+C)
	previoushandler = signal(SIGINT, customHandler);
	// Check the previous handler
	if (previoushandler == SIG_ERR)
	{
		perror("signal");
	}
	else if (previoushandler == SIG_DFL)
	{
		printf("Previous handler was the default handler\n");
	}
	else if (previoushandler == SIG_IGN)
	{
		printf("Previous handler ignored the signal\n");
	}
	else
	{
		printf("Previous handler was a custom handler\n");
	}
	// Rest of the program logic
	return (0);
}
