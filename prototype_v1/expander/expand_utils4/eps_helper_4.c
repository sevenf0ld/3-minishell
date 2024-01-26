/*header*/

#include "tester.h"

// -----------------------------------------//
//				STATIC_LOCAL				//
// -----------------------------------------//
// -----------------------------------------//
//				GLOBAL_MAIN					//
// -----------------------------------------//
void	eu_set_back(char **hd_back, char *str)
{
	int	i;
	int	inquote[2];

	inquote[0] = -1;
	inquote[1] = -1;
	check_free_and_null(hd_back);
	i = 0;
	ite_to_dollar(str, &i, inquote);
	if (str[i] == 36)
	{
		i++;
		while (ft_isalnum(str[i]) && str[i])
			i++;
		if (str[i])
			*hd_back = ft_substr(str, i, ft_strlen(str) - 1);
		else
			*hd_back = ft_strdup("");
	}
}
