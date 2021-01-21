/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:40 by cshelli           #+#    #+#             */
/*   Updated: 2021/01/20 20:13:43 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void parser(t_map *map)
{
	int i;

	i = 0;
	map->map = malloc(sizeof(char *) * 50);
	map->fd = open("map.txt", O_RDONLY);
	map->map[i] = NULL;
	while (get_next_line(map->fd, &map->map[i]))
	{
		i++;
		map->map[i] = NULL;
	}
	printf("%s",map->map[1]);
}
