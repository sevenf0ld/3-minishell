#ifndef RM_QUOTE_H
# define RM_QUOTE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>

void	rm_quote_str_arr(char **str_arr);

int		rq_contain_quotes(char *str);
void	rq_init_holder(char **holder, int size);
void	rq_remove_quotes(char **str_arr, int index);
void	rq_count_size(char *str, int *size);
void	rq_count_size_helper(char *str, int *i, int *count);

#endif