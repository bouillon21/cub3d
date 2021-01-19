/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:55:36 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/09 16:17:21 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
