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

void	set_token_type(t_token **tokens, int (f)(char *s, char *t))
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		if (!f(tmp->token, ">"))
			tmp->symbol = OUTREDIR;
		else if (!f(tmp->token, "<"))
			tmp->symbol = INREDIR;
		else if (!f(tmp->token, ">>"))
			tmp->symbol = ADDEND;
		else if (!f(tmp->token, "<<"))
			tmp->symbol = HEREDOC;
		else if (!f(tmp->token, "|"))
			tmp->symbol = PIPE;
		tmp = tmp->next;
	}
}

/*
	BAD because what if its < infile ls -l | wc -l > outfile
	< would be stored in ptr->cmd
	should check if it also is not a token
	by means of something like set_token_type before set_cmd which iterates over everything in full_cmd after splitting on space
*/
void	set_cmd(char **full_cmd, t_command **c_node)
{
	t_command	*ptr;
	
	ptr = *c_node;
	ptr->cmd = full_cmd[0];
	if (full_cmd[1] == NULL)
		return ;
	if (full_cmd[1][0] == '-')
		ptr->flags = full_cmd[1];
	else
		ptr->input = full_cmd[1];
	/*
	i = -1;
	j = 0;
	while (full_cmd[++i] != NULL)
	{
		//can put outside of the loop and increment i
		if (i == 0)
		{
			ptr->cmd = full_cmd[i];
			continue ;
		}
		if (full_cmd[i][0] == '-')
			ptr->flags = full_cmd[i];
		//malloc first but need the set_token_type thing to know how many words
		else
			ptr->input[j++] = full_cmd[i];
	}
	*/
}

//heap free after use apparently
void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}
