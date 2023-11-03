#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include <errno>

int main() {
    const char *filename = "env.c";

    if (access(filename, R_OK) == 0) {
        printf("File '%s' is readable.\n", filename);
    } else {
        // if (errno == ENOENT) {
            printf("File '%s' does not exist.\n", filename);
        // } else {
        //     perror("access");
        // }
    }

    return 0;
}
