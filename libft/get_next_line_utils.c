/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:24:55 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/17 19:17:10 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2 || !(buf = (char *)malloc(sizeof(*s1) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		buf[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		buf[j] = s2[i];
		j++;
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int symbol)
{
	int count;

	count = 0;
	while (str[count])
	{
		if (str[count] == (char)symbol)
			return (((char *)str + count));
		count++;
	}
	if (str[count] == (char)symbol)
		return (((char *)str + count));
	return (0);
}

char	*ft_strdup(char *src)
{
	int		n;
	char	*buf;

	n = 0;
	if (!(buf = (char *)malloc(ft_strlen(src) * sizeof(char) + 1)))
		return (0);
	while (src[n])
	{
		buf[n] = src[n];
		n++;
	}
	buf[n] = '\0';
	return (buf);
}

void	ft_strcpy(char *destptr, const char *srcptr)
{
	int	i;

	i = 0;
	if (!destptr && !srcptr)
		return ;
	while (srcptr[i])
	{
		destptr[i] = srcptr[i];
		i++;
	}
	destptr[i] = 0;
}
