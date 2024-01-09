# cc -Wall -Wextra -Werror -Wno-unused-variable -fsanitize=address preserve.c && ./a.out

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	n;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		n = ft_strlen(s);
	else
		n = len;
	sub = malloc(n + 1);
	if (!sub)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
			sub[j++] = s[i];
		i++;
	}
	sub[j] = '\0';
	return (sub);
}

void    check_double_quote(char c, int index, bool *s)
{
    if (c == 34 && !*s)
    {
        *s = true;
        fprintf(stderr, "\n\x1b[34mfound starting double quote at %i\x1b[m\n", index);
    }
    else if (c == 34 && *s)
    {
        *s = false;
        fprintf(stderr, "\n\x1b[34mfound closing double quote at %i\x1b[m\n", index);
    }
    else if (*s)
        fprintf(stderr, "%c", c);
}

void    check_single_quote(char c, int index, bool *s)
{
    if (c == 39 && !*s)
    {
        *s = true;
        fprintf(stderr, "\n\x1b[32mfound starting single quote at %i\x1b[m\n", index);
    }
    else if (c == 39 && *s)
    {
        *s = false;
        fprintf(stderr, "\n\x1b[32mfound closing single quote at %i\x1b[m\n", index);
    }
    else if (*s)
        fprintf(stderr, "%c", c);
}

int main()
{
    char *single_str = "i am not in quotes except for \'1. one\' \'2. two\' \'3. three\', they are the exception";
    char *double_str = "i am not in quotes except for \"1. one\" \"2. two\" \"3. three\", they are the exception";
    char *d_in_s_str = "i am not in quotes except for \'\"1. one\"\' \'\"2. two\"\' \'\"3. three\"\', they are the exception";
    char *s_in_d_str = "i am not in quotes except for \"\'1. one\'\" \"\'2. two\'\" \"\'3. three\'\", they are the exception";

    char *str = single_str;
    void (*func)(char, int, bool *) = NULL;
    func = check_single_quote;
    printf("str: %s\n", str);

    bool q = false;
    for (int i = 0; str[i] != '\0'; i++)
    {
        func(str[i], i, &q);
    }
    fprintf(stderr, "\n");
}
