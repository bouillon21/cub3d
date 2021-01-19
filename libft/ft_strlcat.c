/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:57:57 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/05 13:58:55 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	dest_len;
	size_t	src_len;

	count = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dest_len >= size)
		return (src_len + size);
	while (src[count] && (size - 1 > count + dest_len))
	{
		dst[count + dest_len] = src[count];
		count++;
	}
	dst[count + dest_len] = '\0';
	return (dest_len + src_len);
}
