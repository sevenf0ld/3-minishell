#include "mini.h"

typedef struct s_ie
{
	int		i;
	int		j;
	char	*displace;
	int		count;
	char	**exp;
}			t_ie;

static char	**init_expandables(char *to_expand, int len, t_status *stat)
{
	t_ie	ie;

	ie = (t_ie){0};
	while (ie.i < len && to_expand[ie.i] != '\0')
	{
		while (ie.i < len && to_expand[ie.i] != '\0' && to_expand[ie.i] != '$') 
			ie.i++;
		ie.j = ie.i + 1;
		while (ie.j < len && to_expand[ie.j] != '\0'
			&& (to_expand[ie.j] != '\"'
				&& to_expand[ie.j] != 32
				&& to_expand[ie.j] != '$'))
			ie.j++;
		ie.displace = ft_substr(to_expand + ie.i, 0, ie.j - ie.i);
		if (ie.displace && *ie.displace)
			ie.count += 1;
		ie.i += ft_strlen(ie.displace);
	}
	ie.exp = malloc_err(sizeof(char *) * (ie.count + 1), stat);
	ie.exp[ie.count] = NULL;
	return (ie.exp);
}