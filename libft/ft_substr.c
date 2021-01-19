/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:33:11 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/07 21:08:42 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	i;

	i = 0;
	if (!s || !(buf = (char *)malloc(sizeof(*s) * (len + 1))))
		return (0);
	if (start >= ft_strlen((char *)s))
	{
		buf[0] = '\0';
		return (buf);
	}
	while (s[start] && i < len)
	{
		buf[i] = s[start];
		i++;
		start++;
	}
	buf[i] = '\0';
	return (buf);
}
