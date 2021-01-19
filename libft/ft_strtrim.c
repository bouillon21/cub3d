/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:40:06 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/09 16:45:34 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	entry(char const c, char const *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*buf;

	i = 0;
	start = 0;
	end = 0;
	if (!s1 || !set)
		return (0);
	while (s1[start] && entry(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && entry(s1[end - 1], set))
		end--;
	if (!(buf = (char *)malloc(sizeof(*s1) * (end - start + 1))))
		return (0);
	while (start < end)
	{
		buf[i] = s1[start];
		i++;
		start++;
	}
	buf[i] = '\0';
	return (buf);
}
