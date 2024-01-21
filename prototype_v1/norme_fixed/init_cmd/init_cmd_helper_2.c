#include "mini.h"

typedef struct s_cmd_init
{
	int			i;
	t_token		*tmp;
	t_token		*first;
	t_token		**tokens;
	t_command	**cmds;
	t_env		*envs;
	t_status	*stat;
}				t_cmd_init;

void	cmd_init_helper_one(t_cmd_init *ft_db, t_token **token)
{
	ft_db->i = 0;
	ft_db->tmp = *token;
	ft_db->first = *token;
	ft_db->tokens = token;
}

void	cmd_init_helper_two(t_cmd_init *ft_db)
{
	if (ft_db->i == 0)
		*ft_db->cmds = cmd_new(cmd_init_norme(ft_db->first),
				ft_db->i, ft_db->envs, ft_db->stat);
	else
	{
		tmp_cmd = cmd_new(cmd_init_norme(ft_db->first),
				ft_db->i, ft_db->envs, ft_db->stat);
		cmd_add_back(ft_db->cmds, tmp_cmd);
	}
	ft_db->i++;
	ft_db->first = ft_db->tmp->next;
	if (ft_db->i == num_pipes(ft_db->tokens))
	{
		tmp_cmd = cmd_new(cmd_init_norme(ft_db->first),
				ft_db->i, ft_db->envs, ft_db->stat);
		cmd_add_back(ft_db->cmds, tmp_cmd);
	}
}

void	cmd_init(t_token **t, t_command **cmds, t_env *envs, t_status *stat)
{
	t_cmd_init	ft_db;

	ft_db = (t_cmd_init){0};
	cmd_init_helper_one(&ft_db, t);
	ft_db.cmds = cmds;
	ft_db.envs = envs;
	ft_db.stat = stat;
	while (tmp != NULL)
	{
		if (tmp->symbol == PIPE)
			cmd_init_helper_two(&ft_db);
		tmp = tmp->next;
	}
	if (num_pipes(t) == 0)
		*cmds = cmd_new(cmd_init_norme(first), i, envs, stat);
	set_cmd_size(*cmds);
}
