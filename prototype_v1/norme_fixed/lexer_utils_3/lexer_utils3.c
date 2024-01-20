#include "mini.h"

typedef struct s_gek
{
	int		i;
	int		j;
	char	*displace;
	int		k;
	char	**exp;
	int		len_dis;
}			t_gek;

void	gek_helper(t_gek *gek, char *to_expand, int len)
{
	while (gek.i < len && to_expand[gek.i] != '\0'
		&& to_expand[gek.i] != '$')
		gek.i++;
	gek.j = gek.i + 1;
	while (gek.j < len && to_expand[gek.j] != '\0'
		&& (to_expand[gek.j] != '\"'
			&& to_expand[gek.j] != 32
			&& to_expand[gek.j] != '$'))
		gek.j++;
}

char	**get_exp_key(char *to_expand, int len, t_status *stat)
{
	t_gek	gek;	

	gek = (t_gek){0};
	gek.exp = init_expandables(to_expand, len, stat);
	while (gek.i < len && to_expand[gek.i] != '\0')
	{
		gek_helper(&gek, to_expand, len);
		gek.displace = ft_substr(to_expand + gek.i, 0, gek.j - gek.i);
		gek.len_dis = ft_strlen(gek.displace);
		if (gek.displace && *gek.displace)
		{
			if (gek.displace[gek.len_dis - 1] == 39)
				gek.displace = ft_strndup(gek.displace, gek.len_dis - 1);
			gek.exp[gek.k++] = gek.displace;
		}
		gek.i += gek.len_dis;
	}
	return (gek.exp);
}
