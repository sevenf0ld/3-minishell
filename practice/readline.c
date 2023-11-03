#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
// cc -Wall -Wextra -Werror readline.c -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

int	main()
{
	char	*pwd = NULL;
	if (!pwd)
		printf("pwd: %s\n", getcwd(pwd, 100));
	chdir("../..");	
	if (!pwd)
		printf("pwd: %s\n", getcwd(pwd, 100));
	
	DIR	*stream = opendir(".");
	if (!stream)
	{
		fprintf(stderr, "check errno to find out more ");
		perror(NULL);
		return (1);
	}
	struct dirent *direntry;
	int	check_stat;
	struct stat	finfo;
	for (direntry = readdir(stream); direntry != NULL; direntry = readdir(stream))
	{
		check_stat = stat(direntry->d_name, &finfo);
		if (!check_stat)
			printf("%s %lld\n", direntry->d_name, finfo.st_size);
			printf("%s %ld\n", direntry->d_name, finfo.st_mtime);
	}
	closedir(stream);
	
	/*
	char	*input;
	while (1)
	{
		input = readline("prompt> ");
		add_history(input);
	}
	*/
	static	char	*cmd_line = NULL;
	while (1)
	{
		if (cmd_line)
		{
			free(cmd_line);
			//cmd_line is no longer a dangling pointer
			cmd_line = NULL;
		}
		cmd_line = readline("prompt> ");
		/*
		 * shows a bell for blank lines
		 * cmd_line only also works the same but checking before derferencing is good practice in case it is a NULL pointer
		*/
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
		rl_clear_history();
		/*
		 * works with signal handling functions
		printf("input: %s\n", cmd_line);
		rl_replace_line("no", 1);
		rl_redisplay();
		printf("replaced: %s\n", cmd_line);
		*/
	}
}
