/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:13:49 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/20 18:30:34 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init(t_cub3D *cub)
{
	init_texture(&cub->textNO, cub->pars.NO);
	init_texture(&cub->textSO, cub->pars.SO);
	init_texture(&cub->textWE, cub->pars.WE);
	init_texture(&cub->textEA, cub->pars.EA);

	cub->player.pres_w = 0;
	cub->player.pres_a = 0;
	cub->player.pres_s = 0;
	cub->player.pres_d = 0;

	cub->player.posX = 2;
	cub->player.posY = 2;
	cub->player.speed = 0.1;
	cub->player.moveSpeed = 0.1;
	cub->player.rotSpeed = 0.1;

	cub->player.dirX = -1;
	cub->player.dirY = 0;

	cub->player.planeX = 0;
	cub->player.planeY = 0.66;
	cub->player.rot = 0;
}

void raycast(t_cub3D *cub)
{
	int i;

	for (int x = 0; x < cub->pars.sWidth; x++)
	{
		// calculate ray position and direction
		double cameraX = 2 * x / (double)cub->pars.sWidth - 1; //x-coordinate in camera space
		double rayDirX = cub->player.dirX + cub->player.planeX * cameraX;
		double rayDirY = cub->player.dirY + cub->player.planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)cub->player.posX;
		int mapY = (int)cub->player.posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side;	 //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->player.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->player.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->player.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->player.posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			// if(worldMap[mapX][mapY] > 0) hit = 1;
			if (cub->pars.map[mapX][mapY] != '0')
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - cub->player.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cub->player.posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(cub->pars.sHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + cub->pars.sHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->pars.sHeight / 2;
		if (drawEnd >= cub->pars.sHeight)
			drawEnd = cub->pars.sHeight - 1;

		//texturing calculations
		//   int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = cub->player.posY + perpWallDist * rayDirY;
		else
			wallX = cub->player.posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int w;
		int h;
		if (side == 1)
		{
			if (stepY > 0)
			{
				w = cub->textEA.width;
				h = cub->textEA.height;
			}
			else if (stepY < 0)
			{
				w = cub->textWE.width;
				h = cub->textWE.height;
			}
		}
		else
		{
			if (stepX > 0)
			{
				w = cub->textNO.width;
				h = cub->textNO.height;
			}
			else if (stepX < 0)
			{
				w = cub->textSO.width;
				h = cub->textSO.height;
			}
		}
		//x coordinate on the texture
		int texX = (int)(wallX * (double)(w));
		if (side == 0 && rayDirX > 0)
			texX = w - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = w - texX - 1;

		//   TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * h / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - cub->pars.sHeight / 2 + lineHeight / 2) * step;

		int texY;
		int color;
		int y;
		y = 0;
		while (y < drawStart)
		{
			my_mlx_pixel_put(&cub->canvas, x, y, 0x003b5eeb);
			y++;
		}

		while(y < drawEnd)
		{
			texY = (int)texPos;
			texPos += step;
			if (side == 1)
			{
				if (stepY > 0)
					color = my_mlx_pixel_get(&cub->textEA, texX, texY);
				else if (stepY < 0)
					color = my_mlx_pixel_get(&cub->textWE, texX, texY);
			}
			else
			{
				if (stepX > 0)
					color = my_mlx_pixel_get(&cub->textNO, texX, texY);
				else if (stepX < 0)
					color = my_mlx_pixel_get(&cub->textSO, texX, texY);
			}
			my_mlx_pixel_put(&cub->canvas, x, y, color);
			y++;
		}

		//отрисовка
		while (y < cub->pars.sHeight)
		{
			my_mlx_pixel_put(&cub->canvas, x, y, 0x00CF74D3);
			y++;
		}
	}
}

int draw_img(t_cub3D *cub)
{
	mlx_clear_window(cub->canvas.mlx, cub->canvas.mlx_win);
	mlx_destroy_image(cub->canvas.mlx, cub->canvas.img);
	cub->canvas.img = mlx_new_image(cub->canvas.mlx, cub->pars.sWidth, cub->pars.sHeight);
	move_player(cub);
	rotation_player(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->canvas.mlx, cub->canvas.mlx_win, cub->canvas.img, 0, 0);
}

void	init_texture(t_canvas *texture, char *way)
{
	texture->mlx = mlx_init();
	if (!(texture->img = mlx_xpm_file_to_image(&texture->mlx, way, &texture->width, &texture->height)))
		error_message("texture");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

int main()
{
	t_cub3D cub;

	cub.pars.fd = open("map_ahegao.txt", O_RDONLY);
	parser(&cub.pars);
	init(&cub);
// #pragma region //init mlx
// 	cub.canvas.mlx = mlx_init();
// 	cub.canvas.mlx_win = mlx_new_window(cub.canvas.mlx, cub.pars.sWidth, cub.pars.sHeight, "Hi");
// 	cub.canvas.img = mlx_new_image(cub.canvas.mlx, cub.pars.sWidth, cub.pars.sHeight);
// 	cub.canvas.addr = mlx_get_data_addr(cub.canvas.img, &cub.canvas.bits_per_pixel, &cub.canvas.line_length, &cub.canvas.endian);
// #pragma endregion
// 	mlx_hook(cub.canvas.mlx_win, 2, 1L << 0, &press_key, &cub);
// 	mlx_hook(cub.canvas.mlx_win, 3, 1L << 1, &release_key, &cub);
// 	mlx_loop_hook(cub.canvas.mlx, &draw_img, &cub);
// 	mlx_loop(cub.canvas.mlx);
}