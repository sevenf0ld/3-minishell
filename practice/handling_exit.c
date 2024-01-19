#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>

volatile sig_atomic_t eof_flag = 0;

void eof_handler(int signum) {
    (void)signum;  // Unused parameter
    eof_flag = 1;
}

int main() {
    // Set up signal handler for Ctrl+D (EOF)
    signal(SIGINT, SIG_IGN); // Ignore Ctrl+C
    signal(SIGTSTP, SIG_IGN); // Ignore Ctrl+Z
    signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+\
    signal(SIGTERM, SIG_IGN); // Ignore termination signal
    signal(SIGQUIT, eof_handler); // Handle Ctrl+D (EOF)

    char *input;

    while (1) {
        input = readline("Enter something: ");

        // Check if Ctrl+D was pressed
        if (eof_flag) {
            printf("\r");  // Move cursor to the beginning of the line
            printf("Ctrl+D pressed. Exiting.\n");
            free(input);
            break;
        }

        // Your logic with user input goes here

        printf("You entered: %s\n", input);
        free(input);
    }

    return 0;
}
