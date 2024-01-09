// cc -Wall -Wextra -Werror -Wno-unused-variable -fsanitize=address preserve.c && ./a.out

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

void    check_double_quote(char c, int index, bool *d)
{
    if (c == 34 && !*d)
    {
        *d = true;
        fprintf(stderr, "\n\x1b[34mfound starting double quote at %i\x1b[m\n", index);
    }
    else if (c == 34 && *d)
    {
        *d = false;
        fprintf(stderr, "\n\x1b[34mfound closing double quote at %i\x1b[m\n", index);
    }
    else if (*d)
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

int iterate_until_closing(char *s, int start, char c)
{
    int i = start + 1;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            fprintf(stderr, "closing at index %i\n", i);
            return i;
        }
        i++;
    }
    return i;
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
    (void) func;
    printf("str: %s\n", str);

    bool q = false;
    int i = 0;
    int end = 0;
    char *sub = NULL;
    while (str[i] != '\0')
    {
        //func(str[i], i, &q);
        if (str[i] == 39 && !q)
        {
            q = true;
            end = iterate_until_closing(str, i, 39);
            if (i != end)
                sub = ft_substr(str, i, (size_t) end);
            fprintf(stderr, "sub -> %s (start %i) and (end %i)\n", sub, i, end);
            i += end - 1;
            continue ;
        }
        if (str[i] == 39 && q)
            q = false;
        i++;
    }
    fprintf(stderr, "\n");
}
