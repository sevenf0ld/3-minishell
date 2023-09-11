/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:54:11 by maiman-m          #+#    #+#             */
/*   Updated: 2023/09/10 00:11:02 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

int			ft_atoi(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t i, size_t n);
int			ft_isalnum(int i);
int			ft_isalpha(int i);
int			ft_isascii(int i);
int			ft_isdigit(int i);
int			ft_isprint(int i);
char		*ft_itoa(int n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *dst, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(const char *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t n);
size_t		ft_strlen(char const *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *hay, const char *ndl, size_t n);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_toupper(int i);
int			ft_tolower(int i);
int			ft_strcmp(char *s, char *t);
long long	ft_atoll(const char *s);

char		*get_next_line(int fd);
char		*read_and_store(char *store, int fd, char *buffer);
char		*extract_newline(char *store);
char		*update_store(char *store);
int			look_for_nl(char *to_search);

/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
*/

#endif
