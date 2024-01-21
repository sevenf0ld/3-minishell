#include "rm_quote.h"

void	rq_count_size_helper(char *str, int *i, int *count)
{
	int	log;

	if (str[*i] == 34 || str[*i] == 39)
	{
		log = *i;
		(*i)++;
		while (str[*i] != '\0' && str[*i] != str[log])
		{
			(*count)++;
			(*i)++;
		}
	}
}

void	rq_count_size(char *str, int *size)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		rq_count_size_helper(str, &i, &count);
		if (str[i] != '\0')
		{
			if (str[i] != 34 && str[i] != 39)
				count++;
			i++;
		}
	}
	*size = count;
}

void	rq_snq_helper(char *str, char *holder, int *i, int *j)
{
	int	log;

	if (str[*i] == 34 || str[*i] == 39)
	{
		log = *i;
		(*i)++;
		while (str[*i] != '\0' && str[*i] != str[log])
		{
			holder[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	}
}

void	rq_strdup_no_quote(char *str, char *holder)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		rq_snq_helper(str, holder, &i, &j);
		if (str[i] != '\0')
		{
			if (str[i] != 34 && str[i] != 39)
			{
				holder[j] = str[i];
				j++;
			}
			i++;
		}
	}
}

void	rq_remove_quotes(char **str_arr, int index)
{
	int		size;
	char	*holder;

	size = 0;
	rq_count_size(str_arr[index], &size);
	rq_init_holder(&holder, size);
	rq_strdup_no_quote(str_arr[index], holder);
	if (str_arr[index] != NULL)
		free(str_arr[index]);
	str_arr[index] = holder;
}
