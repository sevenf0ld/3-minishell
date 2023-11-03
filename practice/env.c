#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *program = "/bin/ls";
    char *args[] = {program, "F", NULL};

    // Define environment variables
    char *envp[] = {
        "MY_VARIABLE=123",
        "ANOTHER_VARIABLE=abc",
        NULL
    };

    if (execve(program, args, envp) == -1) {
        perror("execve");
        return 1;
    }

    return 0;
}
