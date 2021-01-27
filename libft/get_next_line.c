/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:24:04 by cshelli           #+#    #+#             */
/*   Updated: 2020/11/17 19:29:08 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_sbuf(char **sbuf, char **line)
{
	char		*pointer;
	char		*tmp;

	pointer = NULL;
	if (*sbuf)
	{
		if ((pointer = ft_strchr(*sbuf, '\n')))
		{
			*pointer = '\0';
			*line = ft_strdup(*sbuf);
			tmp = *sbuf;
			*sbuf = ft_strdup((pointer + 1));
			free(tmp);
		}
		else
		{
			*line = ft_strdup(*sbuf);
			free(*sbuf);
			*sbuf = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (pointer);
}

int		get_next_line(int fd, char **line)
{
	static char	*sbuf;
	char		*buf;
	int			count;
	char		*newline;
	char		*tmp;

	buf = NULL;
	if ((read(fd, buf, 0) < 0 || !line || BUFFER_SIZE <= 0) ||
		!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	newline = check_sbuf(&sbuf, line);
	while (!newline && (count = read(fd, buf, BUFFER_SIZE)))
	{
		buf[count] = '\0';
		if ((newline = ft_strchr(buf, '\n')))
		{
			*newline = '\0';
			sbuf = ft_strdup(newline + 1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	free(buf);
	return (count || sbuf) ? 1 : 0;
}
