#include "mini.h"

void	print_map(char **map)
{
	int	y;

	y = 0;
    if (!map)
    {
        printf("NULL");
        return ;
    }
	while (map[y] != NULL)
	{
		ft_putstr_fd("args: ", 1);
		ft_putstr_fd(map[y], 1);
		ft_putstr_fd("\n", 1);
		y++;
	}
}
