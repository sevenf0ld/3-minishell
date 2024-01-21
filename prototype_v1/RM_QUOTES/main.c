#include "rm_quote.h"

static void	debug_print_str(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		if (i == 0)
			printf("[ %s, ", str[i]);
		else if (str[i + 1] == NULL)
			printf("%s ]\n", str[i]);
		else
			printf("%s, ", str[i]);
		i++;
	}
}

static void	free_str_arr(char **str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	main(void)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * 6);
	str[0] = strdup("echo");
	str[1] = strdup("\"asda''sd\"e'hello'");
	str[2] = strdup("'\"dogogo\"'");
	str[3] = strdup("xx\"xx\"xx");
	str[4] = strdup("cat\"'\"1234daad\"'\"");
	str[5] = NULL;

	debug_print_str(str);
	rm_quote_str_arr(str);
	debug_print_str(str);
	free_str_arr(str);
	return (0);
}
