/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:36:03 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/11 17:27:29 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int press_key(int keycode, t_cub3D *cub)
{
	if (keycode == 53)
		exit (0);
	else if (keycode == 124)
		cub->player.pres_d = 1;
	else if (keycode == 125)
		cub->player.pres_s = 1;
	else if (keycode == 123)
		cub->player.pres_a = 1;
	else if (keycode == 126)
		cub->player.pres_w = 1;
}

int release_key(int keycode, t_cub3D *cub)
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

void cast_ray(t_cub3D *cub)
{
	float x;
	float y;
	float c;

	c = 0;
	while (c < 10)
	{
		x = cub->player.x + c * cos(cub->player.rot);
		y = cub->player.y + c * cos(cub->player.rot);
		my_mlx_pixel_put(&cub->canvas, x, y, 0x00FFFFFF);
		c += 1;
	}
	// float x;
	// float y;

	// x = cub->player.x;
	// y = cub->player.y;
	// while (cub->map.map[(int) (y / scale)][(int) (x / scale)] != '1')
	// {
	// 	x += cos(cub->player.rot);
	// 	y += sin(cub->player.rot);
	// 	if (cub->map.map[(int) (y / scale)][(int) (x / scale)] != '1')
	// 		my_mlx_pixel_put(&cub->canvas, x, y, 0x00FFFFFF);
	// }
}

int draw_img(t_cub3D *cub)
{
	move_player(cub);
	mlx_clear_window(cub->mlx, cub->mlx_win);
	mlx_destroy_image(cub->mlx, cub->canvas.img);
	cub->canvas.img = mlx_new_image(cub->mlx, screenWidth, screenHeight);
	draw_map(cub , 0x0044F5A6);
	draw_player(cub, 0x00FFFFFF);
	cast_ray(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->canvas.img, 0, 0);
}

void player_init(t_cub3D *cub)
{
	cub->player.pres_w = 0;
	cub->player.pres_a = 0;
	cub->player.pres_s = 0;
	cub->player.pres_d = 0;
	cub->player.x = 40;
	cub->player.y = 40;
	cub->player.speed = 3;
	cub->player.rot = 4.71;
}

int		main(void)
{
	t_cub3D		cub;

	parser(&cub.map);
	printf("", cub.map.);
	player_init(&cub);
	#pragma region //init mlx
	cub.mlx = mlx_init();
	cub.mlx_win = mlx_new_window(cub.mlx, screenWidth, screenHeight, "Hi");
	cub.canvas.img = mlx_new_image(cub.mlx, screenWidth, screenHeight);
	cub.canvas.addr = mlx_get_data_addr(cub.canvas.img, &cub.canvas.bits_per_pixel, &cub.canvas.line_length, &cub.canvas.endian);
	#pragma endregion	
	mlx_hook(cub.mlx_win, 2, 1L<<0, &press_key, &cub);
	mlx_hook(cub.mlx_win, 3, 1L<<1, &release_key, &cub);
	mlx_loop_hook(cub.mlx, &draw_img, &cub);
	mlx_loop(cub.mlx);
}
