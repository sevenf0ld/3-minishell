/*header*/

#include "tester.h"

// -----------------------------------------//
//				STATIC_LOCAL				//
// -----------------------------------------//
static void	mj_join_and_free(char **s1, char **s2)
{
	char	*holder;

	holder = ft_strjoin(*s1, *s2);
	check_free_and_null(s1);
	*s1 = ft_strdup(holder);
	check_free_and_null(&holder);
}

// -----------------------------------------//
//				GLOBAL_MAIN					//
// -----------------------------------------//
void	check_free_and_null(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	eu_multi_join(char **s0, char **s1, char **s2, char **s3)
{
	char	*holder;

	holder = strdup("");
	mj_join_and_free(&holder, s1);
	mj_join_and_free(&holder, s2);
	mj_join_and_free(&holder, s3);
	check_free_and_null(s0);
	*s0 = strdup(holder);
	check_free_and_null(&holder);
}

void	ite_to_dollar(char *str, int *i, int *inquote)
{
	while (str[*i])
	{
		if (str[*i] == 34)
			(inquote)[0] *= -1;
		if (str[*i] == 39 && (inquote)[0] == -1)
			(inquote)[1] *= -1;
		while ((inquote)[1] == 1 && str[*i] && str[*i + 1] != 39)
			(*i)++;
		if (str[*i] == 36)
			break ;
		(*i)++;
	}
}
