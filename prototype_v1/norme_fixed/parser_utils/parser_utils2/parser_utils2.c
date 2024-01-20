#include "mini.h"

static t_pipe	*retrieve_pipe(t_pipe *p_node, int n)
{
	t_pipe	*end;

	end = p_node;
	while (end != NULL)
	{
		if (end->pos == n)
			break ;
		end = end->next;
	}
	return (end);
}

void	assign_pe_helper(t_command *cur, t_pipe *end, t_pipe *pnode, int i)
{
	if (i == 0)
	{
		end = retrieve_pipe(pnode, cur->pos);
		if (end)
		{
			cur->read_end = STDIN_FILENO;
			cur->write_end = end->pipe_fd[1];
		}
	}
	else if (i == 1)
	{
		end = retrieve_pipe(pnode, cur->pos - 1);
		if (end)
		{
			cur->read_end = end->pipe_fd[0];
			cur->write_end = STDOUT_FILENO;
		}
	}
}

void	assign_pipe_ends(t_command *c_node, t_pipe *p_node)
{
	t_command	*cur;
	t_pipe		*end;

	cur = c_node;
	end = NULL;
	while (cur != NULL)
	{
		if (cur->pos == 0)
			assign_pe_helper(cur, end, p_node, 0);
		if (cur->pos == cur->size - 1)
			assign_pe_helper(cur, end, p_node, 1);
		if (cur->pos > 0 && cur->pos < cur->size - 1)
		{
			end = retrieve_pipe(p_node, cur->pos);
			if (end)
			{
				cur->read_end = end->prev->pipe_fd[0];
				cur->write_end = end->pipe_fd[1];
			}
		}
		cur = cur->next;
	}
}
