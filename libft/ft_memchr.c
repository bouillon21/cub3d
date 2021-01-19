/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:16:55 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/07 16:40:40 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *memptr, int val, size_t num)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char*)memptr;
	while (i < num)
	{
		if (str[i] == (unsigned char)val)
			return ((void *)str + i);
		i++;
	}
	return (0);
}
