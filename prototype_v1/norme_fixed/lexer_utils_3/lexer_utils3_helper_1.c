#include "mini.h"

int	not_standalone_dollar(char *s)
{
	if (!ft_strcmp(s, "$") || !ft_strcmp(s, "\"$\""))
		return (0);
	return (1);
}

void	expansion(t_token **tokens, t_status *stat)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->token, '$'))
			if (not_in_single(tmp->token) && not_standalone_dollar(tmp->token))
				tmp->exp = true;
		tmp = tmp->next;
	}
	expand_env_var(tokens, stat);
}

void	decide_quote(char c, bool *sq, bool *wq)
{
	if (c == 39 && !*sq && !*wq)
		*sq = true;
	else if (c == 34 && !*wq && !*sq)
		*wq = true;
}

int	not_in_single(char *s)
{
	int		i;
	bool	sq;
	bool	wq;

	i = 0;
	sq = false;
	wq = false;
	while (s[i] != '\0')
	{
		if (s[i] == 39 || s[i] == 34)
			decide_quote(s[i], &sq, &wq);
		i++;
	}
	if ((!sq && wq) || (sq && wq))
		return (1);
	return (0);
}

char	*sub_exp(char *s, int len, char **key, char **val)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (key[i] != NULL)
	{
		ret = repl(s, key[i], val[i], len);
		if (ret != NULL)
		{
			s = ret;
			len = ft_strlen(s);
		}
		i++;
	}
	return (ret);
}
