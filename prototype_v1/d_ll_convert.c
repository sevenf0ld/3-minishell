
#include <unistd.h>

typedef struct s_node
{
	int				x;
	char			*str;
	struct s_node	*prev;
	struct s_node	*next;
}t_node;


t_node	*double_ll_convert(t_node **lst)
{
	t_node	*prev;
	t_node	*curr;
	t_node	*tail;

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

// double_ll_convert takes in the root of the linked list and returns
// the tail of the linked list.