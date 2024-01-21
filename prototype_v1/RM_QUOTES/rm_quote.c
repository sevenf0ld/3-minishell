// double quote in ascii is 34 and single quote is 39
#include "rm_quote.h"

int	rq_contain_quotes(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	rq_init_holder(char **holder, int size)
{
	int	i;

	i = 0;
	*holder = (char *)malloc(sizeof(char) * (size + 1));
	if (*holder == NULL)
		return ;
	while (i < size)
	{
		(*holder)[i] = '\0';
		i++;
	}
	(*holder)[size] = '\0';
}


void	rm_quote_str_arr(char **str_arr)
{
	int		i;

	if (str_arr == NULL)
		return ;
	i = 0;
	while (str_arr[i] != NULL)
	{
		if (rq_contain_quotes(str_arr[i]))
			rq_remove_quotes(str_arr, i);
		i++;
	}
}
