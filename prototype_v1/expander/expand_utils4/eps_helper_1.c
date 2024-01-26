/*header*/

#include "tester.h"
// -----------------------------------------//
//				STATIC_LOCAL				//
// -----------------------------------------//
static int	ecd_helper(char *str, int *i, int *j, int *in_quote)
{
	if (str[*i] == 39)
		in_quote[1] *= -1;
	if (str[*i] == 39
		&& str[*i + 1]
		&& str[*i + 1] != str[*i]
		&& in_quote[0] != 1
		&& in_quote[1] == 1)
	{
		*j = *i + 1;
		while (str[*j] != str[*i] && str[*j])
			(*j)++;
		if (str[*j] == str[*i])
		{
			*i = *j;
			in_quote[1] *= -1;
		}
		if (str[*j] == '\0')
			return (1);
	}
	return (0);
}

// -----------------------------------------//
//				GLOBAL_MAIN					//
// -----------------------------------------//
// ascii 36 = '$', 39 = single_quote, 34 = double_quote
// in_quote[0] = double_quote, in_quote[1] = single_quote
int	eu_contain_dollar(char *str)
{
	int	i;
	int	j;
	int	in_quote[2];

	if (str == NULL)
		return (0);
	i = 0;
	in_quote[0] = -1;
	in_quote[1] = -1;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
			in_quote[0] *= -1;
		if (ecd_helper(str, &i, &j, in_quote))
			break ;
		if (str[i] == 36 && str[i + 1] && ft_isalnum(str[i + 1]))
			return (1);
		if (str[i] != '\0')
			i++;
	}
	return (0);
}
