/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:08:23 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/09 11:52:26 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture(t_canvas *texture, char *way)
{
	texture->mlx = mlx_init();
	if (!(texture->img = mlx_xpm_file_to_image(&texture->mlx, way,
	&texture->width, &texture->height)))
		error_message("texture");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
	&texture->line_length, &texture->endian);
}

void	cub_init(t_cub3D *cub)
{
	cub->player.pres_w = 0;
	cub->player.pres_a = 0;
	cub->player.pres_s = 0;
	cub->player.pres_d = 0;
	cub->player.posX = -1;
	cub->player.posY = -1;
	cub->player.speed = 0.1;
	cub->player.moveSpeed = 0.17;
	cub->player.rot_speed = 0.1;
	cub->player.rot = 0;
}

/*
**	init_ray	вычисляем положение и направление луча
**	camX		x-координата в пространстве камеры
**	deltaDist	длина луча
**	hit			столкновение со стеной
*/

void	init_ray(t_cub3D *cub, int x)
{
	cub->draw.camX = 2 * x / (double)cub->pars.sWidth - 1;
	cub->draw.rayDirX = cub->player.dirX + cub->player.planeX *
	cub->draw.camX;
	cub->draw.rayDirY = cub->player.dirY + cub->player.planeY *
	cub->draw.camX;
	cub->draw.mapX = (int)cub->player.posX;
	cub->draw.mapY = (int)cub->player.posY;
	cub->draw.deltaDistX = fabs(1 / cub->draw.rayDirX);
	cub->draw.deltaDistY = fabs(1 / cub->draw.rayDirY);
	cub->draw.hit = 0;
}
