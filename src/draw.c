/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:20:09 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/19 19:38:16 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_canvas *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		my_mlx_pixel_get(t_canvas *texture, int x, int y)
{
	char	*dst;
	int		color;

	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return(color);
}

// void	draw_square(const int x,const int y,int color, t_canvas *img)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	j = -1;
// 	while (++i <= scale)
// 	{
// 		while (++j <= scale) 
// 			my_mlx_pixel_put(img, x + i, y + j, color);
// 		j = -1;
// 	}
// }

// void draw_map(t_cub3D *cub ,int color)
// {
// 	int i;
// 	int j;
// 	int run;
// 	int run2;

// 	i = 0;
// 	j = 0;
// 	run = 0;
// 	run2 = 0;
// 	while (i < 12)
// 	{
// 		while (j < 26)
// 		{
// 			if (cub->map.map[i][j] == '1')
// 				draw_square(j + run, i + run2, color, &cub->canvas);
// 			run += scale;
// 			j++;
// 		}
// 		j = 0;
// 		run = 0;
// 		run2 += scale;
// 		i++;
// 	}
// }

// void draw_player(t_cub3D *cub, int color)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	j = -1;
// 	while (++i <= scale/2)
// 	{
// 		while (++j <= scale/2)
// 			my_mlx_pixel_put(&cub->canvas, cub->player.x + i, cub->player.y + j, color);
// 		j = -1;
// 	}
// }