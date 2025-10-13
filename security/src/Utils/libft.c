#include "../../include/security.h"

size_t	ft_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

bool	ft_isdelim(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

char	*trim_whitespace(const char *str)
{
	unsigned int	i = 0;
	unsigned int	j = ft_strlen(str);
	unsigned int	k = 0;
	char			*dest;

	while(ft_isdelim(str[i]))
		i++;

	while(ft_isdelim(str[j]))
		j--;

	dest = (char *)malloc((j - i + 2) * sizeof(char));
	if (!dest)
		return (NULL);

	while(i + k <= j)
	{
		dest[k] = str[i + k];
		k++;
	}
	dest[k] = '\0';

	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		r;

	i = 0;
	r = 0;
	while (s1[i] != '\0' && i < n && r == 0)
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if (r == 0 && ft_strlen(s1) < ft_strlen(s2) && i < n)
	{
		while (s2[i] != '\0' && i < n)
		{
			r -= (unsigned char)s2[i];
			i++;
		}
	}
	if (r > 0)
		r /= r;
	else if (r < 0)
		r /= -r;
	return (r);
}

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	unsigned int	l;
	char			*dest;
	size_t			i;

	l = (unsigned int)ft_strlen(str);
	i = 0;
	if (l < start || len == 0)
		dest = (char *)malloc(1 * sizeof(char));
	else if ((l - start) > (unsigned int)len)
		dest = (char *)malloc((len + 1) * sizeof(char));
	else
		dest = (char *)malloc((l - start + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len && l > start && str[start] != '\0')
	{
		dest[i] = str[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}