/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:21:27 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/07 19:03:37 by cshelli          ###   ########.fr       */
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
	//How much to increase the texture coordinate per screen pixel
	draw->step = 1.0 * height / draw->lineHeight;
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
	cub->draw.texPos = (cub->draw.drawStart - cub->pars.sHeight / 2 +
	cub->draw.lineHeight / 2) * cub->draw.step;
}
