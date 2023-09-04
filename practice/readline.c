#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

//cc readline.c -lreadline

int	main()
{
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
		//shows a bell for blank lines
		//*cmd_line only also works the same but checking before derferencing is good practice in case it is a NULL pointer
		if (cmd_line && *cmd_line)
			add_history(cmd_line);
	}
}
