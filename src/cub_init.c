/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:08:23 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:48:50 by cshelli          ###   ########.fr       */
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

void	cub_init(t_cub3d *cub)
{
	cub->player.pres_w = 0;
	cub->player.pres_a = 0;
	cub->player.pres_s = 0;
	cub->player.pres_d = 0;
	cub->player.pos_x = -1;
	cub->player.pos_y = -1;
	cub->player.speed = 0.1;
	cub->player.move_speed = 0.17;
	cub->player.rot_speed = 0.1;
	cub->player.rot = 0;
}

/*
**	init_ray	вычисляем положение и направление луча
**	cam_x		x-координата в пространстве камеры
**	deltaDist	длина луча
**	hit			столкновение со стеной
*/

void	init_ray(t_cub3d *cub, int x)
{
	cub->draw.cam_x = 2 * x / (double)cub->pars.s_width - 1;
	cub->draw.ray_dir_x = cub->player.dir_x + cub->player.plane_x *
	cub->draw.cam_x;
	cub->draw.ray_dir_y = cub->player.dir_y + cub->player.plane_y *
	cub->draw.cam_x;
	cub->draw.map_x = (int)cub->player.pos_x;
	cub->draw.map_y = (int)cub->player.pos_y;
	cub->draw.delta_dist_x = fabs(1 / cub->draw.ray_dir_x);
	cub->draw.delta_dist_y = fabs(1 / cub->draw.ray_dir_y);
	cub->draw.hit = 0;
}
