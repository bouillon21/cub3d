/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:49:01 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/05 13:49:46 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		((unsigned char *)memptr)[i] = val;
		i++;
	}
	return ((void *)memptr);
}
