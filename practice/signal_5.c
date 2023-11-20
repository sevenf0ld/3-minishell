#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

static char *pp = NULL;

char *siganl_cntrl_c(char *current_input);
void sighandler_c(int signum);

void sighandler_c(int signum)
{
    printf("\nCtrl+C\n");
    printf(">%s\n", pp);
    siganl_cntrl_c(&pp);
    printf(">>%s\n", pp);
}

char *siganl_cntrl_c(char *current_input)
{
    char *input = NULL;
    signal(SIGINT, sighandler_c);
    while (!input)
    {
        input = readline("prompt> ");
        if (input)
            return input;
        input = NULL;
    }
    return input;
}

int main(void)
{
    char *pipeline;

    pipeline = NULL;
    pipeline = siganl_cntrl_c(pipeline);
    printf("pipeline = %s$\n", pipeline);

    // Perform any necessary cleanup before exiting

    return 0;
}
