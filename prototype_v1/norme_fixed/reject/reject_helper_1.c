#include "mini.h"

static int	multi_redir(t_token *t_node, t_status *stat)
{
	t_token	*tmp;

	tmp = t_node;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE
			|| tmp->symbol == ADD || tmp->symbol == HD)
			if (tmp->next != NULL)
				if (tmp->next->symbol == IN_RE
					|| tmp->next->symbol == OUT_RE
					|| tmp->next->symbol == ADD
					|| tmp->next->symbol == HD)
					return (redir_err(tmp->next->token, stat));
		tmp = tmp->next;
	}
	return (0);
}

static int	redir_as_end(t_token *t_node, t_status *stat)
{
	t_token	*tmp;

	tmp = t_node;
	while (tmp != NULL)
	{
		if (tmp->symbol == IN_RE || tmp->symbol == OUT_RE
			|| tmp->symbol == ADD || tmp->symbol == HD)
			if (tmp->next == NULL || (tmp->next != NULL
					&& tmp->next->symbol == PIPE))
				return (redir_err(NULL, stat));
		tmp = tmp->next;
	}
	return (0);
}

void	mas_helper(t_token *tmp, int *i, char *s, t_token *t_node)
{
	i = 0;
	s = NULL;
	tmp = t_node;
}

int	mas_helper_two(t_token *tmp, int *i, char *s, t_status *stat)
{
	if (tmp->symbol == ARGS)
	{
		s = tmp->token;
		*i = 0;
		while (s[*i] != '\0')
		{
			if (is_delim(s[*i]) && s[*i + 1] != '\0' && is_delim(s[(*i) + 1]))
			{
				if (s[(*i) + 1] == '>')
					return (redir_err(">", stat));
				else
					return (symbols_err(stat));
			}
			(*i)++;
		}
	}
	return (0);
}

static int	multi_adjacent_symbols(t_token *t_node, t_status *stat)
{
	int		i;
	char	*s;
	t_token	*tmp;

	mas_helper(tmp, &i, s, t_node);
	while (tmp != NULL)
	{
		if (mas_helper_two(tmp, &i, s, stat))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
