// cc -Wall -Wextra -Werror -Wno-unused-variable -fsanitize=address preserve.c && ./a.out
// cc -Wall -Wextra -Wno-unused-variable -Wno-unused-but-set-variable preserve.c && ./a.out

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

int	all_whitespace(char *s, int start, int end)
{
    int	i;

    i = start;
    while (s[i] != '\0' && i < end)
    {
        if (s[i] != 32)
            return (0);
        i++;
    }
    return (1);
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
    //fprintf(stderr, "opening at \x1b[34mindex %i (%c)\x1b[m or \x1b[34m index %i (%c)\x1b[m\n", start, s[start], i, s[i]);
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            //fprintf(stderr, "closing at \x1b[34mindex %i (%c)\x1b[m\n", i, s[i]);
            return i;
        }
        i++;
    }
    return i;
}

int main()
{
    char *single_str = "i am       not in quotes except for   \'1. one\' \'2. two\' \'3. three\', they are the exception \'4. four\'";
    char *double_str = "i am not in     quotes except for   \"1. one\" \"2. two\" \"3. three\", they are the exception \"4. four\"";
    char *d_in_s_str = "i am   not in quotes except    for \'\"1. one\"\'     \'\"2. two\"\' \'\"3. three\"\', they are the exception \'\"4.    four\"\'";
    char *s_in_d_str = "i am not in quotes    except for \"\'1. one\'\" \"\'2.     two\'\"      \"\'3. three\'\", they are the exception \"\'5.     five\'\"";

    char *str = double_str;
    printf("\x1b[35mstr: %s\x1b[m\n", str);
    void (*func)(char, int, bool *) = NULL;
    func = check_double_quote;
    (void) func;
    char quote_to_check = 34;

    bool q = false;
    int i = 0;
    int close = 0;
    char *sub = NULL;
    int start = 0;
    int end = ft_strlen(str);
    int num = 0;
    while (str[i] != '\0')
    {
        //func(str[i], i, &q);
        if (str[i] == quote_to_check && !q)
        {
            end = i - 1;
            if (!all_whitespace(str, start, end))
            {
                sub = ft_substr(str, start, (size_t) end - start);
                num += 1;
                fprintf(stderr, "   unquoted ft_substr() =\x1b[36m|%s|\x1b[m\n", sub);
            }
            fprintf(stderr, "\x1b[33m   starts at %i\x1b[m\n", i);
            q = true;
            close = iterate_until_closing(str, i, quote_to_check);
            sub = ft_substr(str, i, (size_t) close - i + 1);
            if (sub != NULL)
                num += 1;
            fprintf(stderr, "   quoted ft_substr() =\x1b[36m|%s|\x1b[m\n", sub);
            i += close - i;
            fprintf(stderr, "\x1b[33m   ends at %i\x1b[m\n", i);
            continue ;
        }
        if (str[i] == quote_to_check && q)
        {
            q = false;
            start = i + 1;
        }
        i++;
    }
    fprintf(stderr, "number: %i\n", num);
}
