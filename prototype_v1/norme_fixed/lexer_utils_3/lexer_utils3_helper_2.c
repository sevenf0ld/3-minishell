#include "mini.h"

char	**get_exp_value(char *to_expand, int len, t_status *stat, char **key)
{
	int		i;
	char	*sub;
	char	**exp;

	i = 0;
	sub = NULL;
	exp = init_expandables(to_expand, len, stat);
	while (key[i] != NULL)
	{
		sub = getenv(key[i] + 1);
		if (sub != NULL)
			exp[i] = sub;
		else
			exp[i] = "";
		i++;
	}
	return (exp);
}

void	expand_env_var(t_token **tokens, t_status *stat)
{
	int		len;
	char	**exp_key;
	char	**exp_value;
	t_token	*tmp;

	tmp = *tokens;
	exp_key = NULL;
	exp_value = NULL;
	while (tmp != NULL)
	{
		if (tmp->exp && ft_strcmp(tmp->token, "$?") != 0)
		{
			len = ft_strlen(tmp->token);
			exp_key = get_exp_key(tmp->token, len, stat);
			exp_value = get_exp_value(tmp->token, len, stat, exp_key);
			tmp->token = sub_exp(tmp->token, len, exp_key, exp_value);
		}
		else if (tmp->exp && !ft_strcmp(tmp->token, "$?"))
			tmp->token = ft_lltoa(stat->s_code);
		tmp = tmp->next;
	}
}
