#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>


struct termios saved;

void restore(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
}


int main() {
    struct termios attributes;

    tcgetattr(STDIN_FILENO, &saved);
    atexit(restore);

    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
    // tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);

    printf("Entering the loop\n");
    while(1) {};
}