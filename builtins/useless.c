void	command_init(t_token *tokens, t_command **cmds, int (f)(char *s, char *t))
{
	t_token	*tmp;
	int		total;
	int		i;

	tmp = tokens;
	total = 0;
	i = -1;
	while (tmp != NULL)
	{
		if (!f(tmp->token, "|"))
			total += 1;
		tmp = tmp->next;
	}

	printf("no. of commands: %i\n", total + 1);

	cmds = malloc(sizeof(t_command) * (total + 1));
	while (++i < total + 1)
	{
		cmds[i]->cmd = NULL;
		cmds[i]->flags = NULL;
		cmds[i]->input = NULL;
		cmds[i]->std_in = -1;
		cmds[i]->std_out = -1;
		cmds[i]->std_err = -1;
		cmds[i]->order = i + 1;
		cmds[i]->next = NULL;
	}
	parser(cmds, total + 1, f, tokens);
}

/*
 * iterate over each token (node)
 * if it is a pipe, that is an indication of a new command (node) for the next token
 * all the token nodes before the pipe token node is a singular command node
 *
 * iterate over each command (node)
 * iterate over each token (node)
 * continously update the token
 * only update the command if the token is a pipe
 */
void	parser(t_command **cmds, int size, int (f)(char *s, char *t), t_token *tokens)
{
	int			i;
	int			j;
	t_command	*cur_cmd;
	t_token		*cur_tok;

	i = 0;
	j = 1;
	cur_cmd = *cmds;
	cur_tok = tokens;
	while (cur_tok != NULL)
	{
		if (!f(cur_tok->token, "|"))
		{
			j = 1;
			cur_cmd = cur_cmd->next;
			continue ;
		}
		if (j == 1)
			cur_cmd->cmd = cur_tok->token;
		else
		{
			if (cur_tok->token[0] == '-')
				cur_cmd->flags = cur_tok->token;
			//else if not token
				//cur_cmd->input = cur_tok->token;
			//else if token
				//redirect
		}
		cur_tok = cur_tok->next;
	}
}
