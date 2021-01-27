/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 20:36:03 by cshelli           #+#    #+#             */
/*   Updated: 2021/01/27 20:43:55 by cshelli          ###   ########.fr       */
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

int draw_img(t_cub3D *cub)
{
	move_player(cub);
	mlx_clear_window(cub->mlx, cub->mlx_win);
	mlx_destroy_image(cub->mlx, cub->canvas.img);
	cub->canvas.img = mlx_new_image(cub->mlx, screenWidth, screenHeight);
	draw_map(cub , 0x0044F5A6);
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
	cub->player.speed = 3;
}

int		main(void)
{
	t_cub3D		cub;

	parser(&cub.map);
	player_init(&cub);
	#pragma region //init mlx
	cub.mlx = mlx_init();
	cub.mlx_win = mlx_new_window(cub.mlx, screenWidth, screenHeight, "Hi");
	cub.canvas.img = mlx_new_image(cub.mlx, screenWidth, screenHeight);
	cub.canvas.addr = mlx_get_data_addr(cub.canvas.img, &cub.canvas.bits_per_pixel,
					&cub.canvas.line_length, &cub.canvas.endian);
	#pragma endregion
	mlx_hook(cub.mlx_win, 2, 1L<<0, &press_key, &cub);
	mlx_hook(cub.mlx_win, 3, 1L<<1, &release_key, &cub);
	mlx_loop_hook(cub.mlx, &draw_img, &cub);
	mlx_loop(cub.mlx);
}
