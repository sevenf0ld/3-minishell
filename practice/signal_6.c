#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdbool.h>

bool	s_flag = false;
// Signal handler function
void sigint_handler(int signum) {
	printf("Caught signal %d (SIGINT)\n", signum);
	s_flag = true;
}

int main()
{
	char	*pipeline = NULL;
	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		perror("Error setting up signal handler");
		return 1;
	}

	printf("Press Ctrl+C to send a SIGINT signal\n");

	// A simple loop to keep the program running
	while(1)
	{
		printf("pipeline >> %s\n",pipeline);
		while (1)
		{
			// Your program logic goes here
			pipeline = readline("p > ");
			if (s_flag == true)
			{
				printf("TRUE\n");
				break;
			}
			// For this example, we'll just sleep for a second
			wait(NULL);
		}
	}
	

	return 0;
	}
