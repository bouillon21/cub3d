/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:40 by cshelli           #+#    #+#             */
/*   Updated: 2021/01/27 18:18:36 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int size_file()
{
	int fd;
	int size;
	char ch;

	size = 0;
	fd = open("map.txt", O_RDONLY);
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
			size++;
	}
	return(++size);
}


void parser(t_map *map)
{
	int i;

	i = 0;
	map->map = calloc(size_file() + 1, sizeof(char *));
	map->fd = open("map.txt", O_RDONLY);
	while (get_next_line(map->fd, &map->map[i]))
		i++;
}
