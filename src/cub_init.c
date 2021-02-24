/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:08:23 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/23 16:10:00 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_texture(t_canvas * texture, char *way)
{
	texture->mlx = mlx_init();
	if (!(texture->img = mlx_xpm_file_to_image(&texture->mlx, way, &texture->width, &texture->height)))
		error_message("texture");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}

void	cub_init(t_cub3D *cub)
{
	cub->player.pres_w = 0;
	cub->player.pres_a = 0;
	cub->player.pres_s = 0;
	cub->player.pres_d = 0;

	POS_X = 2.5;
	POS_Y = 1.5;
	cub->player.speed = 0.1;
	cub->player.moveSpeed = 0.11;
	cub->player.rotSpeed = 0.1;

	DIR_X = -1;
	DIR_Y = 0;

	PLANE_X = 0;
	PLANE_Y = 0.66;
	cub->player.rot = 0;
}