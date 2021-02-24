/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:21:27 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/24 20:47:51 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	step_side(t_draw *draw, t_player *player)
{
	if (draw->rayDirX < 0)
	{
		draw->stepX = -1;
		draw->sideDistX = (player->posX - draw->mapX) * draw->deltaDistX;
	}
	else
	{
		draw->stepX = 1;
		draw->sideDistX = (draw->mapX + 1.0 - player->posX) * draw->deltaDistX;
	}
	if (draw->rayDirY < 0)
	{
		draw->stepY = -1;
		draw->sideDistY = (player->posY - draw->mapY) * draw->deltaDistY;
	}
	else
	{
		draw->stepY = 1;
		draw->sideDistY = (draw->mapY + 1.0 - player->posY) * draw->deltaDistY;
	}
}

void	dda(t_draw *draw, char **map)
{
	while (draw->hit == 0)
	{
		if (draw->sideDistX < draw->sideDistY)
		{
			draw->sideDistX += draw->deltaDistX;
			draw->mapX += draw->stepX;
			draw->side = 0;
		}
		else
		{
			draw->sideDistY += draw->deltaDistY;
			draw->mapY += draw->stepY;
			draw->side = 1;
		}
		if (map[draw->mapX][draw->mapY] == '1')
			draw->hit = 1;
	}
}

void	fish_eye__height_wall(t_draw *draw, t_player *player, int sheight)
{
	if (draw->side == 0)
		draw->perpWallDist = (draw->mapX - player->posX + (1 - draw->stepX) / 2)
		/ draw->rayDirX;
	else
		draw->perpWallDist = (draw->mapY - player->posY + (1 - draw->stepY) / 2)
		/ draw->rayDirY;
	draw->lineHeight = (int)(sheight / draw->perpWallDist);
	draw->drawStart = -draw->lineHeight / 2 + sheight / 2;
	if (draw->drawStart < 0)
		draw->drawStart = 0;
	draw->drawEnd = draw->lineHeight / 2 + sheight / 2;
	if (draw->drawEnd >= sheight)
		draw->drawEnd = sheight - 1;
	if (draw->side == 0)
		draw->wallX = player->posY + draw->perpWallDist *
		draw->rayDirY;
	else
		draw->wallX = player->posX + draw->perpWallDist *
		draw->rayDirX;
	draw->wallX -= floor((draw->wallX));
}

void	tex_size(t_draw *draw, int width, int height)
{
	draw->texX = (int)(draw->wallX * (double)(width));
	if (draw->side == 0 && draw->rayDirX > 0)
		draw->texX = width - draw->texX - 1;
	if (draw->side == 1 && draw->rayDirY < 0)
		draw->texX = width - draw->texX - 1;
	// How much to increase the texture coordinate per screen pixel
	draw->step = 1.0 * height / draw->lineHeight;
}

void	draw_wall(t_cub3D *cub, int x, int y)
{
	while (++y < cub->draw.drawEnd)
	{
		cub->draw.texY = (int)cub->draw.texPos;
		cub->draw.texPos += cub->draw.step;
		if (cub->draw.side == 1)
		{
			if (cub->draw.stepY > 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textEA, cub->draw.texX, cub->draw.texY);
			else if (cub->draw.stepY < 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textWE, cub->draw.texX, cub->draw.texY);
		}
		else
		{
			if (cub->draw.stepX > 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textNO, cub->draw.texX, cub->draw.texY);
			else if (cub->draw.stepX < 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textSO, cub->draw.texX, cub->draw.texY);
		}
		my_mlx_pixel_put(&cub->canvas, x, y, cub->draw.color);
	}
}

void	init_ray(t_cub3D *cub, int x )
{
	// calculate ray position and direction
	cub->draw.camX = 2 * x / (double)cub->pars.sWidth - 1; //x-coordinatein camera space
	cub->draw.rayDirX = cub->player.dirX + cub->player.planeX *
	cub->draw.camX;
	cub->draw.rayDirY = cub->player.dirY + cub->player.planeY *
	cub->draw.camX;
	//which box of the map we're in
	cub->draw.mapX = (int)cub->player.posX;
	cub->draw.mapY = (int)cub->player.posY;
	//length of ray from one x or y-cub->draw.side to next x or y-cub->drawside
	cub->draw.deltaDistX = fabs(1 / cub->draw.rayDirX);
	cub->draw.deltaDistY = fabs(1 / cub->draw.rayDirY);
	cub->draw.hit = 0; //was there a wall cub->draw.hit?
}

void	texture(t_cub3D *cub)
{
	if (cub->draw.side == 1)
		{
			if (cub->draw.stepY > 0)
				tex_size(&cub->draw, cub->textEA.width, cub->textEA.height);
			else if (cub->draw.stepY < 0)
				tex_size(&cub->draw, cub->textWE.width, cub->textWE.height);
		}
		else
		{
			if (cub->draw.stepX > 0)
				tex_size(&cub->draw, cub->textNO.width, cub->textNO.height);
			else if (cub->draw.stepX < 0)
				tex_size(&cub->draw, cub->textSO.width, cub->textSO.height);
		}
		// Starting texture coordinate
		cub->draw.texPos = (cub->draw.drawStart - S_HEIGHT / 2 +
		cub->draw.lineHeight / 2) * cub->draw.step;
}

void	draw_skye_floor(t_cub3D *cub, int x)
{
	int y;

	y = -1;
	while (++y < cub->draw.drawStart)
		my_mlx_pixel_put(&cub->canvas, x, y, 0x003b5eeb);
	y = cub->draw.drawEnd - 1;
	while (++y < S_HEIGHT - 1)
		my_mlx_pixel_put(&cub->canvas, x, y, 0x00CF74D3);
}