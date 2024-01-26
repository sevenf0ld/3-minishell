#include "mini.h"

void	slot_in_token(t_token *n, char *s, t_token **t, char *r)
{
	t_token	*tmp;
	t_token	*new;

	tmp = n;
	new = NULL;
	new = token_new(s, n->stat);
	new->next = n;
	if (n->prev == NULL)
	{
		n->prev = new;
		*t = new;
	}
	else
	{
		new->prev = n->prev;
		n->prev->next = new;
		n->prev = new;
	}
	n->token = r;
	categorize(t);
}

void	sep_delim_helper(char *s, t_token *t_node, t_token **tokens, int i)
{
	if (i > 0)
	{
		slot_in_token(t_node, ft_substr(s, 0, i), tokens,
			ft_substr(s, i, (int)ft_strlen(s)));
	}
	else
	{
		slot_in_token(t_node, ft_substr(s, 0, 2), tokens,
			ft_substr(s, 2, (int)ft_strlen(s)));
	}
}

void	sep_delim_helper_two(char *s, t_token *t_node, t_token **tokens, int i)
{
	if (i > 0)
	{
		slot_in_token(t_node, ft_substr(s, 0, i), tokens,
			ft_substr(s, i, (int)ft_strlen(s)));
	}
	else
	{
		slot_in_token(t_node, ft_substr(s, 0, 2), tokens,
			ft_substr(s, 1, (int)ft_strlen(s)));
	}
}

void	separate_delim(char *s, t_token *t_node, t_token **tokens)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (s[i] != '\0')
	{
		if (is_hd(s, i, len) || is_add(s, i, len))
		{
			sep_delim_helper(s, t_node, tokens, i);
			break ;
		}
		else if (is_pipe(s[i]) || is_in_re(s[i]) || is_out_re(s[i]))
		{
			sep_delim_helper_two(s, t_node, tokens, i);
			break ;
		}
		i++;
	}
}

static size_t	delim_present(char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (s[0] == 39 || s[0] == 34)
		if (s[len - 1] == 39 || s[len - 1] == 34)
			return (0);
	while (s[i] != '\0')
	{
		if (is_delim(s[i]))
			return (1);
		i++;
	}
	return (0);
}
