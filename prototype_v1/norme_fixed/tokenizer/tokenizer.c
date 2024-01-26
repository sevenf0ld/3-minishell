#include "mini.h"

typedef struct s_new_split
{
	char		*str;
	t_token		**tokens;
	t_status	*stat;
	bool		sq;
	bool		wq;
	int			i;
	int			close;
	int			check;
	int			start;
	int			count;
	char		*sub;
}				t_new_split;

void	new_split_helper_one(t_new_split *ft_db, char *s)
{
	ft_db->str = str;
	ft_db->sq = false;
	ft_db->wq = false;
	ft_db->i = 0;
	ft_db->close = 0;
	ft_db->check = 0;
	ft_db->start = -1;
	ft_db->count = 0;
	ft_db->sub = NULL;
}

void	new_split_helper_two_a(t_new_split *ft_db, char *s, int i)
{
	if (i == 1)
	{
		decide_quote(str[ft_db->i], &ft_db->sq, &ft_db->wq);
		if (ft_db->sq || ft_db->wq)
			ft_db->close = iterate_until_closing(str, str[ft_db->i]);
	}
	else if (i == 2)
	{
		ft_db->close += 1;
		if (ft_db->start == -1)
			ft_db->start = ft_db->i;
	}
}

void	new_split_helper_two_b(t_new_split *ft_db, char *s)
{
	ft_db->sub = ft_substr(str, ft_db->start,
			(size_t) ft_db->i - ft_db->start);
	if (!all_whitespace(ft_db->sub))
		token_init(ft_db->sub, ft_db->tokens,
			ft_db->stat, ft_db->count);
	else
	{
		free(ft_db->sub);
		ft_db->sub = NULL;
	}
	ft_db->count += 1;
	ft_db->start = -1;
}

int	new_split_helper_two(t_new_split *ft_db, char *str)
{
	if (str[ft_db->i] == 39 || str[ft_db->i] == 34)
		new_split_helper_two_a(ft_db, str, 1);
	if (str[ft_db->i] != 32 || (str[ft_db->i] == 32
			&& (ft_db->sq || ft_db->wq)))
		new_split_helper_two_a(ft_db, str, 2);
	else if (str[ft_db->i] == 32 && (!ft_db->wq && !ft_db->sq))
	{
		if (ft_db->check != ft_db->close)
		{
			ft_db->check = ft_db->close;
			return (1);
		}
		new_split_helper_two_b(ft_db, str);
	}
	return (0);
}

void	new_split(char *str, t_token **tokens, t_status *stat)
{
	t_new_split	ft_db;

	ft_db = (t_new_split){0};
	ft_db.tokens = tokens;
	ft_db.stat = stat;
	new_split_helper_one(&ft_db, str);
	while (str[ft_db.i] != '\0')
	{
		if (new_split_helper_two(&ft_db, str))
			continue ;
		(fd_db.i)++;
	}
	token_init(ft_substr(str, ft_db.start,
			(size_t)(ft_db.i) - (ft_db.start)),
		tokens, stat, ft_db.count);
}
