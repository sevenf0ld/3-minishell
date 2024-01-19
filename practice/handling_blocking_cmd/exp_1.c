#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigint_handler(int signum) {
    // Handle SIGINT signal
    printf("SIGINT received. Performing cleanup...\n");
    // Add any necessary cleanup code here
    exit(EXIT_SUCCESS);
}

int main() {
    signal(SIGINT, sigint_handler);

    while (1) {
        // Your code for reading and parsing user input goes here

        // Assume command is stored in the cmd variable
        char* cmd = "cat"; // Replace with user input

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            // Set up signal handler for SIGINT if needed
            signal(SIGINT, SIG_DFL); // Default behavior for SIGINT in the child process

            // Execute the command
            execlp(cmd, cmd, (char *)NULL);

            // If execlp fails, print an error
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) {
                // The child process was terminated by SIGINT
                printf("Child process terminated by SIGINT.\n");
            }
        }
    }

    return 0;
}
