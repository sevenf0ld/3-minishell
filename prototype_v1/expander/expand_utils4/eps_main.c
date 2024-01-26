/*header*/

#include "tester.h"
// -----------------------------------------//
//				STATIC_LOCAL				//
// -----------------------------------------//
static void	ini_holders(char **h1, char **h2, char **h3)
{
	*h1 = NULL;
	*h2 = NULL;
	*h3 = NULL;
}

static void	reset_holders(char **h1, char **h2, char **h3)
{
	check_free_and_null(h1);
	check_free_and_null(h2);
	check_free_and_null(h3);
}

static void	free_and_dup(char **str, char *holder)
{
	check_free_and_null(str);
	*str = strdup(holder);
	check_free_and_null(&holder);
}

// -----------------------------------------//
//				GLOBAL_MAIN					//
// -----------------------------------------//
void	expand_utils(char **str)
{
	char	*holder;
	char	*hd_front;
	char	*hd_expand;
	char	*hd_back;

	if (*str == NULL)
		return ;
	holder = ft_strdup(*str);
	ini_holders(&hd_front, &hd_expand, &hd_back);
	while (eu_contain_dollar(holder))
	{
		eu_set_front(&hd_front, holder);
		eu_set_expand(&hd_expand, holder);
		eu_set_back(&hd_back, holder);
		eu_multi_join(&holder, &hd_front, &hd_expand, &hd_back);
		reset_holders(&hd_front, &hd_expand, &hd_back);
	}
	if (strcmp(*str, holder) != 0)
		free_and_dup(str, holder);
	else
		check_free_and_null(&holder);
}
