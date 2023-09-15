
#include "mini.h"

t_token	*double_ll_convert(t_token **lst)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*tail;

	if (*lst == NULL)
		return (NULL);
	prev = NULL;
	curr = *lst;
	while (curr != NULL)
	{
		curr->prev = prev;
		prev = curr;
		curr = curr->next;
	}
	tail = prev;
	return (tail);
}

// typedef struct s_token
// {
// 	int				x;
// 	char			*str;
// 	struct s_token	*prev;
// 	struct s_token	*next;
// }t_token;
// double_ll_convert takes in the root of the linked list and returns
// the tail of the linked list.
