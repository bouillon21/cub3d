/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:40 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/11 16:24:02 by cshelli          ###   ########.fr       */
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
	// char *line;
	// t_list *head;

	// head = NULL;
	// line = NULL;
	i = 0;
	map->map = calloc(size_file() + 1, sizeof(char *));
	map->fd = open("map.txt", O_RDONLY);
	while (get_next_line(map->fd, &map->map[i]))
		i++;
	// 	ft_lstadd_back(&head, ft_lstnew(line));
	// ft_lstadd_back(&head, ft_lstnew(line));
}
