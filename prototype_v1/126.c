//clang -Wall -Werror -Wextra -fsanitize=address 126.c -o 126

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: ./126 ./[exe]\n");
		return -1;
	}
	/*
	int ret = system(argv[1]);
	if (ret == -1)
		perror(NULL);
	else
		fprintf(stderr, "success\n");
	*/
	///*
	pid_t pid = fork();
	if (!pid)
	{
		//char *first = "bash";
		char *exec[] = {argv[1], NULL};
		//char *exec[] = {first, argv[1] + 2, NULL};
		for (int i = 0; exec[i] != NULL; i++)
			fprintf(stdout, "exec[%i] %s\n", i, exec[i]);
		execve(argv[1], exec, NULL);
		//execve(first, exec, NULL);
		fprintf(stderr, "i failed\n");
		perror(NULL);
	}
	else
	{	
		int	wstat;
		int	got_pid;
		int	e_c = 0;
		do
		{
			got_pid = wait(&wstat);
			if (got_pid == pid)
				break ;
			if (got_pid == -1)
			{
				perror("waitpid");
				return -1;
			}
		}
		while (got_pid == wait(&wstat));
		if (WIFEXITED(wstat))
			e_c = WEXITSTATUS(wstat);
		else if (WIFSIGNALED(wstat))
			e_c = WTERMSIG(wstat);
		else if (WIFSTOPPED(wstat))
			e_c = WIFSTOPPED(wstat);
		else
			fprintf(stderr, "this is not caught\n");
		printf("exit with %i\n", e_c);
	}
	//*/
}
