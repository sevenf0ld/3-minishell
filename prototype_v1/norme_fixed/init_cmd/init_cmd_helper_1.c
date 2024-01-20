#include "mini.h"

void	cmd_add_back(t_command **head, t_command *node)
{
	t_command	*old_end;

	if (!node)
		return ;
	old_end = cmd_last(*head);
	old_end->next = node;
}

static void	set_cmd_size(t_command *head)
{
	int			n;
	t_command	*tmp;

	n = cmd_size(head);
	tmp = head;
	while (tmp != NULL)
	{
		tmp->size = n;
		tmp = tmp->next;
	}
}

static char	*cmd_init_norme(t_token *first)
{
	char	*cmd;
	t_token	*tmp;

	tmp = first;
	cmd = NULL;
	while (tmp != NULL && tmp->symbol != PIPE)
	{
		if (tmp->symbol == CMD)
			cmd = tmp->token;
		tmp = tmp->next;
	}
	return (cmd);
}

static int	num_pipes(t_token **tokens)
{
	int		i;
	t_token	*tmp;

	tmp = *tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->symbol == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
