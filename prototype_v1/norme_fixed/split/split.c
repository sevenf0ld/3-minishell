#include "mini.h"

/*
   split the symbol(s) concatenated to other characters if q is false
   | > < >> <<
*/
void	split_tokens(t_token **tokens, t_status *stat)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		categorize_symbol(tokens);
		if (tmp->symbol == CMD || tmp->symbol == ARGS
			|| tmp->symbol == FILN || tmp->symbol == LIM)
		{
			if (delim_present(tmp->token))
			{
				separate_delim(tmp->token, tmp, tokens, stat);
				while (tmp->prev != NULL)
					tmp = tmp->prev;
				continue ;
			}
		}
		tmp = tmp->next;
	}
}
