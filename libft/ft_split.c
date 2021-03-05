/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:11:39 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/05 17:07:43 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_str(char const *s, char c)
{
	int	i;
	int	pnt;

	i = 0;
	pnt = 0;
	while (s[pnt] != '\0')
	{
		if ((s[pnt] == c && (s[pnt + 1] != c || s[pnt + 1] != '\0'))
			|| (s[pnt] != c && s[pnt + 1] == '\0'))
			i++;
		pnt++;
	}
	return (i);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	int		strsum;
	char	**pars;

	if (!s)
		return (NULL);
	pars = malloc(size_str(s, c) * sizeof(char *) + 1);
	if (pars == NULL)
		return (NULL);
	i = 0;
	strsum = 0;
	start = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && (s[i + 1] != c || s[i + 1] != '\0'))
			start = i + 1;
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			pars[strsum++] = ft_substr(s, start, i - start + 1);
		i++;
	}
	pars[strsum] = NULL;
	return (pars);
}
