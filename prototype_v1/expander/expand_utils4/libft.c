/*header*/

#include "tester.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	s3 = malloc(strlen(s1) + strlen(s2) + 1);
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		s3[j++] = s2[i++];
	s3[j] = '\0';
	return (s3);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	n;

	if (!s)
		return (NULL);
	if (strlen(s) < len)
		n = strlen(s);
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

char	*ft_strndup(const char *s, int n)
{
	char	*str;
	int		i;

	str = malloc(n + 1);
	i = -1;
	while (i < n && s[++i] != '\0')
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

int	ft_isalnum(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	if (i >= 'a' && i <= 'z')
		return (1);
	if (i >= 'A' && i <= 'Z')
		return (1);
	return (0);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	len;
	char	*dst;

	len = ft_strlen(str);
	dst = malloc(sizeof(*dst) * (len + 1));
	if (dst)
	{
		i = 0;
		while (str[i] != '\0')
		{
			dst[i] = str[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}
