#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
    for (int i = 0; envp[i] != NULL; i++)
    {
        if (!strncmp(envp[i], "OLDPWD", strlen("OLDPWD")))
            fprintf(stderr, "%s\n", envp[i]);
    }
}
