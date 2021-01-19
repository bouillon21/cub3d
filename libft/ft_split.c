/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:11:39 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/10 18:55:40 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_worlds(const char *s, char c)
{
	size_t	i;
	int		rez;

	i = 0;
	rez = 0;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) ||
			(s[i] != c && !s[i + 1]))
			rez++;
		i++;
	}
	return (rez);
}

static char		**wipe(char **result, int g)
{
	while (g >= 0)
	{
		free(result[g]);
		g--;
	}
	free(result);
	return (0);
}

static void		print(char *dst, char const *start, char c)
{
	size_t i;

	i = 0;
	while (start[i] != c && start[i] != '\0')
	{
		dst[i] = start[i];
		i++;
	}
	dst[i] = '\0';
}

static char		**rezult(const char *s, int j, char **buf, char c)
{
	size_t g;
	size_t i;

	i = j + 1;
	g = 0;
	while (s[i] && ft_strlen(s) >= i)
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]))
		{
			if (!(buf[g] = (char*)malloc(i - j + 1)))
				return (wipe(buf, --g));
			print(buf[g++], s + j, c);
			j = i + 1;
		}
		i++;
	}
	if (ft_strlen(s) >= i)
	{
		buf[g] = (char *)malloc(i - j + 1);
		print(buf[g++], s + j, c);
	}
	buf[g] = NULL;
	return (buf);
}

char			**ft_split(char const *s, char c)
{
	char	**buf;
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	if (!s || !(buf = (char **)malloc(
		(count_worlds(s, c) + 1) * sizeof(char *))))
		return (0);
	while (s[i++] == c)
		j++;
	if (i >= ft_strlen(s))
	{
		buf[0] = NULL;
		return (buf);
	}
	buf = rezult(s, j, buf, c);
	if (!buf)
		return (0);
	return (buf);
}
