/*header*/

#include "tester.h"

int	main(int argc, char **argv)
{
	char	*str;

	if (argc == 2)
	{
		str = strdup(argv[1]);
		expand_utils(&str);
		printf("str : %s\nresult : %s\n", argv[1], str);
		free(str);
	}
	else
		printf("Usage : ./a.out (str)\n");
	return (0);
}
