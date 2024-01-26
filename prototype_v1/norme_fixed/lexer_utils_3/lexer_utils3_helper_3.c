#include "mini.h"

typedef struct s_repl
{
	char	*og;
	char	*displace;
	char	*sub;
	int		len_og;
	int		len_dis;
	int		len_sub;
	int		occur;
	char	*shift;
	char	*extracted;
	int		diff;
	char	*ret;
	char	*tmp;
	int		moved;
}	t_repl;

void	repl_helper_one(t_repl *r, int i)
{
	if (i == 0)
	{
		r->len_dis = strlen(r->displace);
		r->len_sub = strlen(r->sub);
		r->occur = -1;
		r->shift = r->og;
		r->extracted = strstr(r->shift, r->displace);
	}
	else if (i == 1)
	{
		r->diff = r->len_sub - r->len_dis;
		r->ret = malloc(sizeof(char) * (r->len_og + (r->diff * r->occur) + 1));
		r->tmp = r->ret;
	}
	else if (i == 2)
	{
		r->shift = strstr(r->og, r->displace);
		r->moved = r->shift - r->og;
		strncpy(r->tmp, r->og, r->moved);
		r->tmp += r->moved;
		strcpy(r->tmp, r->sub);
		r->tmp += r->len_sub;
		r->og += r->moved + r->len_dis;
	}
}

char	*repl(char *og, char *displace, char *sub, int len_og)
{
	t_repl	r;

	r = (t_repl){0};
	r.og = og;
	r.displace = displace;
	r.sub = sub;
	r.len_og = len_og;
	repl_helper_one(&r, 0);
	while (r.extracted != NULL)
	{
		r.occur++;
		r.extracted = strstr(r.shift, r.displace);
		if (r.extracted != NULL)
			r.shift = r.extracted + r.len_dis;
	}
	repl_helper_one(&r, 1);
	while (r.occur-- && r.occur >= 0)
		repl_helper_one(&r, 2);
	strcpy(r.tmp, r.og);
	return (r.ret);
}
