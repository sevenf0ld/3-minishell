#include <stdio.h>

int main() {
    // Move the cursor to the end of the current line
    printf("This is some text that goes beyond the end of the line\r");

    // Print additional content
    printf("New content after moving to the end of the line\n");

    return 0;
}
