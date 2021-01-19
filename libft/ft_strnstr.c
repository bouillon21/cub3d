/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:29:15 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/05 15:29:21 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *need, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (need[0] == '\0')
		return ((char *)s);
	while (s[i] && i < len)
	{
		while (s[i + j] == need[j] && need[j] && i + j < len)
			j++;
		if (!need[j])
			return ((char *)&s[i]);
		i++;
		j = 0;
	}
	return (0);
}
