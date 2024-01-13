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

int iterate_until_closing(char *s, char c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            return i;
        }
        i++;
    }
    return i;
}

int main()
{
    char *single_str = "i am       not in quotes except for   \'1. one\' \'2. two\' \'3. three\', they are the exception \'4. four\'5.five";
    char *double_str = "i am not in     quotes except for   \"1. one\" \"2. two\" \"3. three\", they are the exception \"4. four\"5.five";
    char *d_in_s_str = "i am   not in quotes except    for \'\"1. one\"\'     \'\"2. two\"\' \'\"3. three\"\', they are the exception \'\"4.    four\"\'5.five";
    char *s_in_d_str = "i am not in quotes    except for \"\'1. one\'\" \"\'2.     two\'\"      \"\'3. three\'\", they are the exception \"\'5.     five\'\"5.five";

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
    int check;
    int start = 0;
    int end = 0;
    while (str[i] != '\0')
    {
        //func(str[i], i, &q);
        if (str[i] == quote_to_check && !q)
        {
            q = true;
            close = iterate_until_closing(str, quote_to_check);
        }
        else if (str[i] == quote_to_check && q)
        {
            q = false;
        }
        if (str[i] != 32 || (str[i] == 32 && q))
        {
            close += 1;
            printf("|%c|    %i, %i\n", str[i], close, i);
        }
        else if (str[i] == 32 && !q)
        {
            //fprintf(stderr, "%s (%i, %i)\n", str + i, close, i);
            if (!start)
                start = i;
            if (start && !end)
                end  = i;
            // skip the spaces outside of quotes
            //if (check != close)
            //{
            //    check = close;
            //    fprintf(stderr, "(%i, %i) %i\n", close, i, check);
            //    fprintf(stderr, "substr %s (start: %i, end %i)\n", ft_substr(str, start, (size_t) end - start), start, end);
            //}
            check = close;
            fprintf(stderr, "(%i, %i) %i\n", close, i, check);
            fprintf(stderr, "substr %s (start: %i, end %i)\n", ft_substr(str, start, (size_t) end - start), start, end);
        }
        i++;
    }
}
