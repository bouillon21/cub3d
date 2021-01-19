/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:30:50 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/05 15:31:40 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int symbol)
{
	int count;

	count = ft_strlen((char *)str);
	while (count >= 0)
	{
		if (str[count] == symbol)
			return (((char *)str + count));
		count--;
	}
	return (0);
}
