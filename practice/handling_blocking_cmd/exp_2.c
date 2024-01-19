#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// Global variable to store the PID of the child process
pid_t child_pid;

// Signal handler for SIGINT
void sigint_handler(int signum) {
    (void) signum;  // Unused parameter

    // Send SIGINT to the child process
    if (child_pid > 0) {
        kill(child_pid, SIGINT);
    }
}

int main() {
    // Set up the SIGINT signal handler
    signal(SIGINT, sigint_handler);

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
        child_pid = pid;

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            // Command exited normally
            printf("Command exited with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            // Command terminated by a signal
            printf("Command terminated by signal: %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
