#include "mini.h"

bool	is_pipe(char a)
{
	if (a == 124)
		return (true);
	return (false);
}

bool	is_in_re(char a)
{
	if (a == 60)
		return (true);
	return (false);
}

bool	is_out_re(char a)
{
	if (a == 62)
		return (true);
	return (false);
}

bool	is_add(char *s, size_t i, size_t len)
{
	if (i + 1 >= len)
		return (false);
	if (is_out_re(s[i]) && is_out_re(s[i + 1]))
		return (true);
	return (false);
}

bool	is_hd(char *s, size_t i, size_t len)
{
	if (i + 1 >= len)
		return (false);
	if (is_in_re(s[i]) && is_in_re(s[i + 1]))
		return (true);
	return (false);
}
