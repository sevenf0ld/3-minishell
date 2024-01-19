#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <sys/wait.h>

struct termios original_termios;

void restore_terminal_settings() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void sigint_handler(int signum) {
    (void) signum;  // Unused parameter

    // Print a newline after receiving Ctrl+C
    printf("\n");
}

int main() {
    // Save original terminal settings
    tcgetattr(STDIN_FILENO, &original_termios);

    // Set up signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    while (1) {
        // Print your prompt here (e.g., "prompt> ")

        // Your code for reading and parsing user input goes here
        // ...

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp("cat", "cat", (char *)NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                // Command exited normally
                // Add your logic here
            } else if (WIFSIGNALED(status)) {
                // Command terminated by a signal
                // Add your logic here
            }
        }
    }

    // Restore original terminal settings before exiting
    restore_terminal_settings();

    return 0;
}
