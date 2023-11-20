#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// volatile sig_atomic_t	interrupted = 0;
// 		// Flag to indicate if Ctrl+C was pressed

void	sigint_handler(int signum)
{
	sig_atomic_t	interrupted;

	interrupted = 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	printf("Press Ctrl+C to trigger the signal handler...\n");
	// while (!interrupted)
	// {
	// 	// Your program logic here
	// }
	printf("Ctrl+C was pressed, handling the signal...\n");
	// Continue with your program's logic after handling Ctrl+C
	return (0);
}
