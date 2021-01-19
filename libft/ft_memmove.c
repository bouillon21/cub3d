/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:48:08 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/07 14:46:52 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destptr, const void *srcptr, size_t n)
{
	if (!srcptr && !destptr)
		return (NULL);
	if (destptr < srcptr)
		return (ft_memcpy(destptr, srcptr, n));
	while (n)
	{
		((char *)destptr)[n - 1] = ((char *)srcptr)[n - 1];
		n--;
	}
	return (destptr);
}
