/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:21:32 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/21 19:50:12 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	valid_map(t_cub3D *cub)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (cub->pars.map[i])
	{
		j = 0;
		while (cub->pars.map[i][j])
		{
			if (cub->pars.map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	cub->count_sprites = count;
	cub->sprites = malloc(sizeof(t_sprite *) * count);

	i = 0;
	count = 0;
	while (cub->pars.map[i])
	{
		j = 0;
		while (cub->pars.map[i][j])
		{
			if (cub->pars.map[i][j] == '2')
			{
				cub->sprites[count].x = i + 0.5;
				cub->sprites[count].y = j + 0.5;
				count++;
			}
			j++;
		}
		i++;
	}
}