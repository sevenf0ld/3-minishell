#include "mini.h"

// cmd_new helper functions
void	cmd_new_helper_one(t_command *node)
{
	node->pos = n;
	node->size = 0;
	node->cmd = cmd;
	node->args = NULL;
	node->num_a = 0;
	node->lim = NULL;
	node->num_l = 0;
	node->std_in = NULL;
	node->num_si = 0;
	node->std_out_o = NULL;
}

void	cmd_new_helper_two(t_command *node)
{
	node->num_so_o = 0;
	node->std_out_a = NULL;
	node->num_so_a = 0;
	node->read_end = -1;
	node->write_end = -1;
	node->og = NULL;
	node->last_out = INT_MIN;
	node->exec = true;
}

// cmd_new
t_command	*cmd_new(char *cmd, int n, t_env *envs, t_status *stat)
{
	t_command	*node;

	node = malloc_err(sizeof(t_command), stat);
	cmd_new_helper_one(node);
	cmd_new_helper_two(node);
	node->builtin = is_builtin(cmd);
	node->env_var = envs;
	node->stat = stat;
	node->next = NULL;
	return (node);
}
