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

void    decide_quote(char c, bool *sq, bool *wq)
{
    if (c == 39 && !*sq)
        *sq = true;
    else if (c == 34 && !*wq)
        *wq = true;
    else if (c == 39 && *sq)
        *sq = false;
    else if (c == 34 && *wq)
        *wq = false;
}

void    preserve(char *str)
{
    fprintf(stderr, "\x1b[35mstr: %s\x1b[m\n", str);
    bool q = false;
    (void) q;
    bool sq = false;
    bool wq = false;
    int i = 0;
    int close = 0;
    int check;
    int start = -1;
    while (str[i] != '\0')
    {
        if (str[i] == 39 || str[i] == 34)
        {
            decide_quote(str[i], &sq, &wq);
            if (sq || wq)
                close = iterate_until_closing(str, str[i]);
        }
        if (str[i] != 32 || (str[i] == 32 && (sq || wq)))
        {
            close += 1;
            if (start == -1)
                start = i;
        }
        else if (str[i] == 32 && (!wq && !sq))
        {
            // skip the spaces outside of quotes
            if (check != close)
            {
                check = close;
                //fprintf(stderr, "SUBSTR-> %s\n", ft_substr(str, start, (size_t) i - start));
                continue ;
            }
            fprintf(stderr, "SUBSTR-> %s\n", ft_substr(str, start, (size_t) i - start));
            start = -1;
        }
        i++;
    }
    fprintf(stderr, "SUBSTR-> %s\n", ft_substr(str, start, (size_t) i - start));

}

int main()
{
    char *single_str = "i am not in quotes except for \'1. one\' \'2. two\' \'3. three\', they are the exception \'4. four\'5.five";
    char *double_str = "i am not in quotes except for \"1. one\" \"2. two\" \"3. three\", they are the exception \"4. four\"5.five";
    char *d_in_s_str = "i am not in quotes except for \'\"1. one\"\' \'\"2. two\"\' \'\"3. three\"\', they are the exception \'\"4. four\"\'5.five";
    char *s_in_d_str = "i am not in quotes except for \"\'1. one\'\" \"\'2. two\'\" \"\'3. three\'\", they are the exception \"\'4. four\'\"5.five";
    char *mess = "\'single\' \"double\" \'\"d_in_s\"\' \"\'s_in_d\'\"";
    char *stick = "hi\'single\'hello hello\"double\"hi hello\'\"d_in_s\"\'hello hi\"\'s_in_d\'\"hi";
    char *multi = "strong \'slim shady in quotes\' \'    \', weak \"mike posner in quotes\" \"    \"";

    char *str = single_str;
    //fprintf(stderr, "\x1b[35mstr: %s\x1b[m\n", str);
    preserve(str);
    
    preserve(double_str);
    preserve(d_in_s_str);
    preserve(s_in_d_str);
    preserve(mess);
    preserve(stick);
    preserve(multi);
}
