/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:36:03 by cshelli           #+#    #+#             */
/*   Updated: 2021/01/24 14:21:34 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void draw_player(t_cub3D *cub, int color)
{
	draw_square(cub->player.x,cub->player.y,color, &cub->canvas);
}

void swith_key(int keycode, t_cub3D *cub)
{
	if (keycode == 53)
	{
		mlx_destroy_window(cub->mlx, cub->mlx_win);
		exit (0);
	}
	else if (keycode == 124)
		cub->player.pres_d = 1;
	else if (keycode == 125)
		cub->player.pres_s = 1;
	else if (keycode == 123)
		cub->player.pres_a = 1;
	else if (keycode == 126)
		cub->player.pres_w = 1;
}

void k(int keycode, t_cub3D *cub)
{
	if (keycode == 124)
		cub->player.pres_d = 0;
	else if (keycode == 125)
		cub->player.pres_s = 0;
	else if (keycode == 123)
		cub->player.pres_a = 0;
	else if (keycode == 126)
		cub->player.pres_w = 0;
}

void move_player(t_cub3D *cub)
{
	if (cub->player.pres_w)
		cub->player.y -= cub->player.speed;
	if (cub->player.pres_a)
		cub->player.x -= cub->player.speed;
	if (cub->player.pres_s)
		cub->player.y += cub->player.speed;
	if (cub->player.pres_d)
		cub->player.x += cub->player.speed;
}

void draw_img(t_cub3D *cub)
{
	move_player(cub);
	mlx_clear_window(cub->mlx, cub->mlx_win);
	mlx_destroy_image(cub->mlx, cub->canvas.img);
	cub->canvas.img = mlx_new_image(cub->mlx, screenWidth, screenHeight);
	draw_map(cub, 0x0044F5A6);
	draw_player(cub, 0x00FFFFFF);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->canvas.img, 0, 0);
}

void player_init(t_cub3D *cub)
{
	cub->player.pres_w = 0;
	cub->player.pres_a = 0;
	cub->player.pres_s = 0;
	cub->player.pres_d = 0;
	cub->player.x = 20;
	cub->player.y = 20;
	cub->player.speed = 1;
}

int		main(void)
{
	t_cub3D		cub;

	player_init(&cub);
	#pragma region //init mlx
	cub.mlx = mlx_init();
	cub.mlx_win = mlx_new_window(cub.mlx, screenWidth, screenHeight, "Hi");
	cub.canvas.img = mlx_new_image(cub.mlx, screenWidth, screenHeight);
	cub.canvas.addr = mlx_get_data_addr(cub.canvas.img, &cub.canvas.bits_per_pixel,
					&cub.canvas.line_length, &cub.canvas.endian);
	#pragma endregion 
	mlx_hook(cub.mlx_win, 2, 1L<<0, swith_key, &cub);
	mlx_hook(cub.mlx_win, 3, 1L<<1, k, &cub);
	mlx_loop_hook(cub.mlx, draw_img, &cub);
	mlx_loop(cub.mlx);
}
