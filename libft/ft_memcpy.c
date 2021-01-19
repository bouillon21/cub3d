/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:46:32 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/05 13:47:19 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destptr, const void *srcptr, size_t num)
{
	size_t	i;

	i = 0;
	if (!destptr && !srcptr)
		return (NULL);
	while (i < num)
	{
		((char *)destptr)[i] = ((char *)srcptr)[i];
		i++;
	}
	return (destptr);
}
