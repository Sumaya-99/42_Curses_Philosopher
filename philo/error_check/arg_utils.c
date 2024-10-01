/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:44:53 by suhelal           #+#    #+#             */
/*   Updated: 2024/09/06 09:12:52 by suhelal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a] != '\0')
		a++;
	return (a);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	b;

	if (!dstsize)
		return (ft_strlen(src));
	b = 0;
	while (b < (dstsize - 1) && src[b] != '\0')
	{
		dst[b] = src[b];
		b++;
	}
	dst[b] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
	{
		str = (char *)malloc(1);
		if (!str)
			free_str(str);
		str[0] = '\0';
		return (str);
	}
	if (len > (slen - start))
		len = (slen - start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

void	ft_free_str(char **spl)
{
	int	i;

	i = 0;
	while (spl[i])
	{
		free (spl[i]);
		i++;
	}
	free (spl);
	write(2, "Error: Only integars are acceptable\n", 37);
}
