#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h> //or termcap.h
#include <string.h>
//cc -Wall -Wextra -Werror -fsanitize=address -lcurses tty.c
//cc -Wall -Wextra -Werror -fsanitize=address -ltermcap tty.c

int	main(int argc, char **argv)
{
	int	fd = open("test.txt", O_RDONLY);
	if (dup2(STDIN_FILENO, fd) == -1)
		fprintf(stderr, "something is wrong w test.txt\n");
	//dup2(fd, STDERR_FILENO);
	if (isatty(fd))
		printf("associated with a terminal\n");
	else
		fprintf(stderr, "what is a termina-\n");
	printf("file %s\n in %s\n out %s\n err %s\n", ttyname(fd), ttyname(STDIN_FILENO), ttyname(STDOUT_FILENO), ttyname(STDERR_FILENO));
	printf("current slot: %i\n", ttyslot());
	printf("SHELL=%s\nUSER=%s\nLOGNAME=%s\nHOME=%s\nMAIL=%s\nBULLSHIT=%s\n", getenv("SHELL"), getenv("USER"), getenv("LOGNAME"), getenv("HOME"), getenv("MAIL"), getenv("BULLSHIT"));

	printf("\n\n");

	/*
	 * home, lang - not sp, acc
	 * user - err
	 * term - acc
	 */
	if (argc == 2)
	{
		char *termtype = getenv(argv[1]);
		if (!termtype)
		   fprintf(stderr, "terminal type not specified\n");
		char	*buf = malloc(sizeof(char) * 2048);
		//static char	buf[2048];
		int	check_getent = tgetent(buf, termtype);
		if (check_getent < 0)
			fprintf(stderr, "error\n");
		else if (check_getent == 1)
			fprintf(stderr, "accessible but what's the type\n");
		else
			printf("something something\n");

		printf("height: %i\n", tgetnum("li"));
		printf("width: %i\n", tgetnum("co"));
	}
}
