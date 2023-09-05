#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	main()
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
	printf("SHELL=%s\nUSER=%s\nLOGNAME=%s\nHOME=%s\nMAIL=%s\n", getenv("SHELL"), getenv("USER"), getenv("LOGNAME"), getenv("HOME"), getenv("MAIL"));
}
