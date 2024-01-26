/*header*/

#include "tester.h"

// -----------------------------------------//
//				STATIC_LOCAL				//
// -----------------------------------------//
// -----------------------------------------//
//				GLOBAL_MAIN					//
// -----------------------------------------//
// 36 = $, 34 = ", 39 = '
void	eu_set_front(char **hd_front, char *str)
{
	int	i;
	int	inquote[2];

	inquote[0] = -1;
	inquote[1] = -1;
	check_free_and_null(hd_front);
	i = 0;
	ite_to_dollar(str, &i, inquote);
	if (str[i] == 36)
		*hd_front = ft_strndup(str, i);
}
