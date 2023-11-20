#include <stdio.h>
#include <readline/readline.h>
// #include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
// #include "/usr/local/Cellar/readline/8.2.1/include/readline/readline.h"


// void sighandler(int signum)
// {
//     printf("\n");
//     rl_replace_line("", 1); // clears written line
//     rl_on_new_line(); // set readline cursor to a newline/nextline
//     rl_redisplay(); // refresh the display with update changes
// }

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


void sighandler_c(int signum)
{
	ft_putstr_fd("\b\b  ", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
    // rl_on_new_line(); // set readline cursor to a newline/nextline
    // rl_redisplay(); // refresh the display with update changes
	ft_putstr_fd("minishell > ", STDERR_FILENO);
	signum = 0;
}



int main() {
    char* input;

    input = NULL;
    signal(SIGINT, sighandler_c);
    while (1) {
        input = readline("Enter something: ");
        if (input)
            break;
    }

    printf("Result: %s\n", input);
    free(input);
    return 0;
}