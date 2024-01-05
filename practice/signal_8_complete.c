#include <stdio.h>
#include </usr/local/opt/readline/include/readline/readline.h>
#include </usr/local/opt/readline/include/readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>

char *input;

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}


void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void sig_int(int signum)
{
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_replace_line("", STDIN_FILENO);
    rl_on_new_line();
    rl_redisplay();
}

void sig_quit(int signum)
{
    // ft_putstr_fd("\b\b  ", STDERR_FILENO);
    printf("\n");
    rl_replace_line("", STDIN_FILENO); // clears written line
    rl_on_new_line(); // set readline cursor to a newline/nextline
    rl_redisplay(); // refresh the display with update changes
}

int main() {
    // char* input;

    input = NULL;
    signal(SIGINT, sig_int);
    signal(SIGQUIT, sig_quit);
    while (1) {
        input = readline("Enter something: ");
        if (input)
            break;
    }

    printf("Result: %s\n", input);
    free(input);
    return 0;
}

// #include "../prototype_v1/mini.h"

// gcc -lreadline -L/goinfre/folim/.brew/opt/readline/lib -I/goinfre/folim/.brew/opt/readline/include signal_8_complete.c -o signal_8_complete.out
// gcc -lreadline -L/goinfre/folim/.brew/opt/readline/lib -I/goinfre/folim/.brew/opt/readline/include signal_8_complete.c ../prototype_v1/libft/libft.a -o signal_8_complete.out

//gcc -lreadline -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib signal_8_complete.c -o signal_8_complete.out