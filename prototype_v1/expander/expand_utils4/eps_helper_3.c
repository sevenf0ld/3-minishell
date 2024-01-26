/*header*/

#include "tester.h"

// -----------------------------------------//
//				STATIC_LOCAL				//
// -----------------------------------------//
static void	se_insert_expandable(char *str, int *i, int *j, char **holder)
{
	*j = *i + 1;
	while (ft_isalnum(str[*j]) && str[*j])
		(*j)++;
	*holder = ft_substr(str, *i + 1, *j - *i - 1);
}

static void	se_insert_converted_exp(char *src, char **dst)
{
	if (getenv(src) != NULL)
		*dst = ft_strdup(getenv(src));
	else
		*dst = ft_strdup("");
}

// -----------------------------------------//
//				GLOBAL_MAIN					//
// -----------------------------------------//
void	eu_set_expand(char **hd_expand, char *str)
{
	int		i;
	int		j;
	char	*holder;
	int		inquote[2];

	inquote[0] = -1;
	inquote[1] = -1;
	check_free_and_null(hd_expand);
	i = 0;
	ite_to_dollar(str, &i, inquote);
	if (str[i] == 36)
		se_insert_expandable(str, &i, &j, &holder);
	se_insert_converted_exp(holder, hd_expand);
	check_free_and_null(&holder);
}
