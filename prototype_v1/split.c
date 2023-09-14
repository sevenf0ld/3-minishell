//cc -Wall -Werror -Wextra -fsanitize=address -g3 split.c -o minishell_split

//run the shell script with ./split.sh

#include <stdio.h>
#include <stdlib.h>

int	white(char a)
{
	if (a == 32 || (a >= 9 && a <= 13))
		return (1);
	return (0);
}

int	is_delim(char a, char *delim, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (a == delim[i])
			return (1);
		i++;
	}
	return (0);
}

int	w_c(char *s, char *delim, size_t n)
{
	int	i = 0;
	int count = 0;
	int	reset = 0;
	while (s[i] != '\0')
	{
		if (is_delim(s[i], delim, n))
			count += 1;
		else if (!white(s[i]) && reset == 0 && !is_delim(s[i], delim, n))
		{
			count += 1;
			reset = 1;
		}
		else if (white(s[i]))
			reset = 0;
		i++;
	}
	return (count);
}

char	*ft_strndup(char *s, int n)
{
	char *str = malloc(n + 1);
	int i;
	for (i = 0; i < n && s[i] != '\0'; i++)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

int	w_l(char *s, char *delim, size_t n)
{
	int i = 0;
	while (s[i] != '\0' && !white(s[i]) && !is_delim(s[i], delim, n))
		i++;
	return (i);
}

char	**ft_split(char *str, char *delim, size_t n)
{
	int	i = 0;
	int j = 0;
	int	count = w_c(str, delim, n);
	char **end = malloc(sizeof(char *) * (count + 1));
	while (str[i] != '\0')
	{
		if (white(str[i]))
			i += 1;
		else
		{
			if (is_delim(str[i], delim, n))
			{
				end[j] = malloc(sizeof(char) + 1);
				end[j][0] = str[i];
				end[j][1] = '\0';
				i += 1;
			}
			else
			{
				end[j] = ft_strndup(str + i, w_l(str + i, delim, n));
				i += w_l(str + i, delim, n);
			}
			j += 1;
		}
	}
	end[j] = NULL;
	return (end);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		fprintf(stderr, "TWO ARGUMENTS NEEDED\n");
		return (1);
	}
	char delim[] = {124, 62, 60, 34, 39};
	size_t	size = sizeof(delim) / sizeof(delim[0]);

	char **end = ft_split(argv[1], delim, size);
	for (int i = 0; end[i] != NULL; i++)
		printf("%s\n", end[i]);
	for (int i = 0; end[i] != NULL; i++)
		free(end[i]);
	free(end);
}
