/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:59:39 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/07 18:39:57 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_size(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	sr(int size, char *buf, int n, int flag)
{
	while (size > flag)
	{
		buf[size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
}

char		*ft_itoa(int n)
{
	char	*buf;
	int		size;

	size = num_size(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!n || !(buf = (char *)malloc((size) * sizeof(char) + 1)))
		return (0);
	buf[size] = '\0';
	if (n < 0)
	{
		buf[0] = '-';
		n *= -1;
		sr(size, buf, n, 1);
	}
	else
		sr(size, buf, n, 0);
	return (buf);
}
