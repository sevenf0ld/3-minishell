/*header*/

#ifndef TESTER_H
# define TESTER_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

//libft
int		ft_isalnum(int i);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *s, int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);

//expander
void	expand_utils(char **str);
void	check_free_and_null(char **str);
void	ite_to_dollar(char *str, int *i, int *inquote);
int		eu_contain_dollar(char *str);
void	eu_set_front(char **hd_front, char *str);
void	eu_set_expand(char **hd_expand, char *str);
void	eu_multi_join(char **s0, char **s1, char **s2, char **s3);
void	eu_set_back(char **hd_back, char *str);

#endif