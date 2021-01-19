/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:00:49 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/05 16:43:09 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *destptr, const char *srcptr, size_t size)
{
	size_t	i;

	i = 0;
	if (!destptr && !srcptr)
		return (0);
	if (size > 0)
	{
		while (srcptr[i] && i < (size - 1))
		{
			destptr[i] = srcptr[i];
			i++;
		}
		destptr[i] = 0;
	}
	while (srcptr[i])
		i++;
	return (i);
}
