/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:54:19 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/05 13:55:01 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int symbol)
{
	int count;

	count = 0;
	while (str[count])
	{
		if (str[count] == (char)symbol)
			return (((char *)str + count));
		count++;
	}
	if (str[count] == (char)symbol)
		return (((char *)str + count));
	return (0);
}
