/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:28:55 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/25 21:17:00 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	sp_post_dist(t_cub3D *cub, int i, int *sporder)
{
	//translate sprite position to relative to camera
	cub->draw.spriteX = cub->sprites[sporder[i]].x - cub->player.posX;
	cub->draw.spriteY = cub->sprites[sporder[i]].y - cub->player.posY;
	//required for correct matrix multiplication
	cub->draw.invDet = 1.0 / (cub->player.planeX * cub->player.dirY -
								cub->player.dirX * cub->player.planeY);
	cub->draw.transformX = cub->draw.invDet * (cub->player.dirY *
	cub->draw.spriteX - cub->player.dirX * cub->draw.spriteY);
	cub->draw.transformY = cub->draw.invDet * (-cub->player.planeY *
	cub->draw.spriteX + cub->player.planeX * cub->draw.spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
	cub->draw.spriteScreenX = (int)((cub->pars.sWidth / 2) *
			(1 + cub->draw.transformX / cub->draw.transformY));
	//parameters for scaling and moving the sprites
}

void	sp_height_width(t_draw *draw, t_pars *pars)
{
	//calculate height of the sprite on screen
	draw->spriteHeight = abs((int)(pars->sHeight / (draw->transformY))); //using 'cub->draw.transformY' instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current x
	draw->drawStartY = -draw->spriteHeight / 2 + pars->sHeight / 2;
	if (draw->drawStartY < 0)
		draw->drawStartY = 0;
	draw->drawEndY = draw->spriteHeight / 2 + pars->sHeight / 2;
	if (draw->drawEndY >= pars->sHeight)
		draw->drawEndY = pars->sHeight - 1;
	//calculate width of the sprite
	draw->spriteWidth = abs((int)(pars->sHeight / (draw->transformY)));
	draw->drawStartX = -draw->spriteWidth / 2 + draw->spriteScreenX;
	if (draw->drawStartX < 0)
		draw->drawStartX = 0;
	draw->drawEndX = draw->spriteWidth / 2 + draw->spriteScreenX;
	if (draw->drawEndX >= pars->sWidth)
		draw->drawEndX = pars->sWidth - 1;
}

void	sp_sort_dist(t_cub3D *cub, int *sp_order, double *sp_dis)
{
	int i;

	i = -1;
	while (++i < cub->count_sprites)
	{
		sp_order[i] = i;
		sp_dis[i] = ((cub->player.posX - cub->sprites[i].x) *
					(cub->player.posX - cub->sprites[i].x) +
					(cub->player.posY - cub->sprites[i].y) *
					(cub->player.posY - cub->sprites[i].y));
	}
	sort_sprites(sp_order, sp_dis, cub->count_sprites);
}

void	sp_draw(t_cub3D *cub, double *zbuf)
{
	int x;
	int y;
	int d;

	x = cub->draw.drawStartX - 1;
	while (++x < cub->draw.drawEndX)
	{
		y = cub->draw.drawStartY - 1;
		cub->draw.texX = (int)(256 * (x - (-cub->draw.spriteWidth / 2 +
		cub->draw.spriteScreenX)) *
								cub->textS.width / cub->draw.spriteWidth) / 256;
		if (cub->draw.transformY > 0 && x > 0 &&
			x < cub->pars.sWidth && cub->draw.transformY < zbuf[x])
			while (++y < cub->draw.drawEndY)
			{
				d = (y) * 256 - cub->pars.sHeight * 128 +
				cub->draw.spriteHeight * 128;
				cub->draw.texY = ((d * cub->textS.height) /
				cub->draw.spriteHeight) / 256;
				cub->draw.color = my_mlx_pixel_get(&cub->textS,
												cub->draw.texX, cub->draw.texY);
				if ((cub->draw.color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&cub->canvas, x, y, cub->draw.color);
			}
	}
}