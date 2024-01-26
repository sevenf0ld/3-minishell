#include "mini.h"

void	decide_quote(char c, bool *sq, bool *wq)
{
	if (c == 39 && !*sq && !*wq)
		*sq = true;
	else if (c == 34 && !*wq && !*sq)
		*wq = true;
	else if (c == 39 && *sq && !*wq)
		*sq = false;
	else if (c == 34 && *wq && !*sq)
		*wq = false;
}

int	unterm_q_norme(bool sq, bool wq, t_status *stat)
{
	if (sq && !wq)
		return (quote_err("\'", stat));
	else if (wq && !sq)
		return (quote_err("\"", stat));
	return (0);
}

typedef struct	s_un_quotes
{
	int		i;
	bool	sq;
	bool	wq;
	char	*s;
	t_token	*tmp;
}				t_un_quotes;

int	unterminated_quotes(t_token *t_node, t_status *stat)
{
	t_un_quotes	db;

	db = (t_un_quotes){0, false, false, NULL, t_node};
	while (db.tmp != NULL)
	{
		if (db.tmp->symbol == ARGS)
		{
			db.s = db.tmp->token;
			db.i = 0;
			db.sq = false;
			db.wq = false;
			while (db.s[db.i] != '\0')
			{
				if (db.s[db.i] == 39 || db.s[db.i] == 34)
					decide_quote(db.s[db.i], &db.sq, &db.wq);
				db.i++;
			}
			if (unterm_q_norme(db.sq, db.wq, stat))
				return (1);
		}
		db.tmp = db.tmp->next;
	}
}
