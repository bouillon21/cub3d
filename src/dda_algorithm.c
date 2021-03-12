/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:21:27 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:57:08 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_side(t_draw *draw, t_player *player)
{
	if (draw->ray_dir_x < 0)
	{
		draw->step_x = -1;
		draw->side_dist_x = (player->pos_x - draw->map_x) * draw->delta_dist_x;
	}
	else
	{
		draw->step_x = 1;
		draw->side_dist_x = (draw->map_x + 1.0 - player->pos_x)
			* draw->delta_dist_x;
	}
	if (draw->ray_dir_y < 0)
	{
		draw->step_y = -1;
		draw->side_dist_y = (player->pos_y - draw->map_y) * draw->delta_dist_y;
	}
	else
	{
		draw->step_y = 1;
		draw->side_dist_y = (draw->map_y + 1.0 - player->pos_y)
			* draw->delta_dist_y;
	}
}

void	dda(t_draw *draw, char **map)
{
	while (draw->hit == 0)
	{
		if (draw->side_dist_x < draw->side_dist_y)
		{
			draw->side_dist_x += draw->delta_dist_x;
			draw->map_x += draw->step_x;
			draw->side = 0;
		}
		else
		{
			draw->side_dist_y += draw->delta_dist_y;
			draw->map_y += draw->step_y;
			draw->side = 1;
		}
		if (map[draw->map_x][draw->map_y] == '1')
			draw->hit = 1;
	}
}

void	fish_eye__height_wall(t_draw *draw, t_player *player, int sheight)
{
	if (draw->side == 0)
		draw->perp_wall_dist = (draw->map_x - player->pos_x
			+ (1 - draw->step_x) / 2) / draw->ray_dir_x;
	else
		draw->perp_wall_dist = (draw->map_y - player->pos_y
			+ (1 - draw->step_y) / 2) / draw->ray_dir_y;
	draw->line_height = (int)(sheight / draw->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + sheight / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + sheight / 2;
	if (draw->draw_end >= sheight)
		draw->draw_end = sheight - 1;
	if (draw->side == 0)
		draw->wall_x = player->pos_y + draw->perp_wall_dist *
		draw->ray_dir_y;
	else
		draw->wall_x = player->pos_x + draw->perp_wall_dist *
		draw->ray_dir_x;
	draw->wall_x -= floor((draw->wall_x));
}

void	tex_size(t_draw *draw, int width, int height)
{
	draw->tex_x = (int)(draw->wall_x * (double)(width));
	if (draw->side == 0 && draw->ray_dir_x > 0)
		draw->tex_x = width - draw->tex_x - 1;
	if (draw->side == 1 && draw->ray_dir_y < 0)
		draw->tex_x = width - draw->tex_x - 1;
	draw->step = 1.0 * height / draw->line_height;
}

void	texture(t_cub3d *cub)
{
	if (cub->draw.side == 1)
	{
		if (cub->draw.step_y > 0)
			tex_size(&cub->draw, cub->text_ea.width, cub->text_ea.height);
		else if (cub->draw.step_y < 0)
			tex_size(&cub->draw, cub->text_we.width, cub->text_we.height);
	}
	else
	{
		if (cub->draw.step_x > 0)
			tex_size(&cub->draw, cub->text_no.width, cub->text_no.height);
		else if (cub->draw.step_x < 0)
			tex_size(&cub->draw, cub->text_so.width, cub->text_so.height);
	}
	cub->draw.tex_pos = (cub->draw.draw_start - cub->pars.s_height / 2 +
	cub->draw.line_height / 2) * cub->draw.step;
}
