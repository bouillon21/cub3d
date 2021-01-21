/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:36:03 by cshelli           #+#    #+#             */
/*   Updated: 2021/01/21 18:11:49 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void parser(t_map *map)
// {
// 	int i;

// 	i = 0;
// 	map->map = malloc(sizeof(char *) * 50);
// 	map->fd = open("map.txt", O_RDONLY);
// 	map->map[i] = NULL;
// 	while (get_next_line(map->fd, &map->map[i]))
// 	{
// 		i++;
// 		map->map[i] = NULL;
// 	}
// 	printf("%s",map->map[1]);
// }

void	my_mlx_pixel_put(t_canvas *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(const int x,const int y,int color, t_canvas *img)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i <= scale)
	{
		while (++j <= scale) 
			my_mlx_pixel_put(img, x + i, y + j, color);
		j = -1;
	}
}

void draw_map(t_canvas *img ,int color)
{
	int i;
	int j;
	int run;
	int run2;

	i = 0;
	j = 0;
	run = 0;
	run2 = 0;
	while (i < 24)
	{
		while (j < 24)
		{
			if (worldMap[i][j] == 1)
				draw_square(j + run, i + run2, color, img);
			run += scale;
			j++;
		}
		j = 0;
		run = 0;
		run2 += scale;
		i++;
	}
}

void close_prog(int keycode, t_cub3D *cub)
{
	if (keycode == 53)
	{
		mlx_destroy_window(cub->mlx, cub->mlx_win);
		exit (0);
	}
}

int		main(void)
{
	t_cub3D		cub;

	cub.mlx = mlx_init();
	cub.mlx_win = mlx_new_window(cub.mlx, 1920, 1080, "Hi");
	cub.canvas.img = mlx_new_image(cub.mlx, 1920, 1080);
	cub.canvas.addr = mlx_get_data_addr(cub.canvas.img, &cub.canvas.bits_per_pixel,
					&cub.canvas.line_length, &cub.canvas.endian);
	draw_map(&cub.canvas, 0x0044F5A6);
	mlx_hook(cub.mlx_win, 2, 1L<<0, close_prog, &cub);
	mlx_put_image_to_window(cub.mlx, cub.mlx_win, cub.canvas.img, 0, 0);
	mlx_loop(cub.mlx);
}