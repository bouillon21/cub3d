/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 19:03:16 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/07 19:17:59 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		count;
	char	*buf;

	count = 0;
	if (!s || !f || !(buf = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	while (s[count])
	{
		buf[count] = f((unsigned char)count, s[count]);
		count++;
	}
	buf[count] = '\0';
	return (buf);
}
