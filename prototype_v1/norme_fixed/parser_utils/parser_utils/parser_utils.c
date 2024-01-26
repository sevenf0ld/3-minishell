#include "mini.h"

typedef struct s_smf
{
	t_token		**tokens;
	t_command	*c_node;
	t_token		*tmp;
	int			i;
	int			j;
	int			k;
}	t_smf;

void	smf_helper(t_smf *smf, int i)
{
	if (i == 0)
	{
		if (smf.tmp->prev->symbol == IN_RE)
			smf.c_node->std_in[smf.i++] = open_err(
					smf.tmp->token, O_RDONLY, 0444, smf.c_node);
		if (smf.tmp->prev->symbol == OUT_RE)
		{
			smf.c_node->std_out_o[smf.j++] = open_err(
					smf.tmp->token, O_CREAT | O_WRONLY
					| O_TRUNC, 0777, smf.c_node);
			smf.c_node->last_out = smf.c_node->std_out_o[smf.j - 1];
		}
		if (smf.tmp->prev->symbol == ADD)
		{
			smf.c_node->std_out_a[smf.k++] = open_err(
					smf.tmp->token, O_CREAT | O_WRONLY
					| O_APPEND, 0666, smf.c_node);
			smf.c_node->last_out = smf.c_node->std_out_a[smf.k - 1];
		}
	}
}

void	set_multi_fildes(t_token **tokens, t_command *c_node)
{
	t_smf	smf;

	smf = (t_smf){0};
	smf.tmp = *tokens;
	smf.c_node = c_node;
	smf.tokens = tokens;
	while (smf.tmp != NULL)
	{
		if (smf.tmp->symbol == FILN && smf.tmp->prev != NULL)
			smf_helper(&smf, 0);
		if (smf.tmp->end == true)
			break ;
		smf.tmp = smf.tmp->next;
	}
	if (smf.c_node->num_si > 0)
		smf.c_node->std_in[smf.i] = INT_MIN;
	if (smf.c_node->num_so_o > 0)
		smf.c_node->std_out_o[smf.j] = INT_MIN;
	if (smf.c_node->num_so_a > 0)
		smf.c_node->std_out_a[smf.k] = INT_MIN;
}

void	imr_helper(t_token *tmp, t_command *c_node)
{
	if (tmp->symbol == FILN && tmp->prev != NULL)
	{
		if (tmp->prev->symbol == IN_RE)
			c_node->num_si += 1;
		if (tmp->prev->symbol == OUT_RE)
			c_node->num_so_o += 1;
		if (tmp->prev->symbol == ADD)
			c_node->num_so_a += 1;
	}
}

void	init_multi_redir(t_token **tokens, t_command *c_node)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		imr_helper(tmp, c_node);
		if (tmp->end == true)
			break ;
		tmp = tmp->next;
	}
	if (c_node->num_si > 0)
		c_node->std_in = malloc_err(
				sizeof(int) * (c_node->num_si + 1), c_node->stat);
	if (c_node->num_so_o > 0)
		c_node->std_out_o = malloc_err(
				sizeof(int) * (c_node->num_so_o + 1), c_node->stat);
	if (c_node->num_so_a > 0)
		c_node->std_out_a = malloc_err(
				sizeof(int) * (c_node->num_so_a + 1), c_node->stat);
	set_multi_fildes(tokens, c_node);
}
