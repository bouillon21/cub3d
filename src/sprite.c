/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:28:55 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:58:57 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	spriteXY	переводим положение спрайта относительно камеры
**	inv_det		требуется для правильного умножения матриц
**	transformXY	расстояние от спрайта до игрока
*/

void	sp_post_dist(t_cub3d *cub, int i, int *sporder)
{
	cub->draw.sprite_x = cub->sprites[sporder[i]].x - cub->player.pos_x;
	cub->draw.sprite_y = cub->sprites[sporder[i]].y - cub->player.pos_y;
	cub->draw.inv_det = 1.0 / (cub->player.plane_x * cub->player.dir_y
		- cub->player.dir_x * cub->player.plane_y);
	cub->draw.transform_x = cub->draw.inv_det * (cub->player.dir_y
		* cub->draw.sprite_x - cub->player.dir_x * cub->draw.sprite_y);
	cub->draw.transform_y = cub->draw.inv_det * (-cub->player.plane_y
		* cub->draw.sprite_x + cub->player.plane_x * cub->draw.sprite_y);
	cub->draw.sprite_screen_x = (int)((cub->pars.s_width / 2)
		* (1 + cub->draw.transform_x / cub->draw.transform_y));
}

/*
** используем transform_y для предотврощения рыбьего глаза
*/

void	sp_height_width(t_draw *draw, t_pars *pars)
{
	draw->sprite_height = abs((int)(pars->s_height / (draw->transform_y)));
	draw->draw_start_y = -draw->sprite_height / 2 + pars->s_height / 2;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = draw->sprite_height / 2 + pars->s_height / 2;
	if (draw->draw_end_y >= pars->s_height)
		draw->draw_end_y = pars->s_height - 1;
	draw->sprite_width = abs((int)(pars->s_height / (draw->transform_y)));
	draw->draw_start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_end_x >= pars->s_width)
		draw->draw_end_x = pars->s_width - 1;
}

void	sp_sort_dist(t_cub3d *cub, int *sp_order, double *sp_dis)
{
	int i;

	i = -1;
	while (++i < cub->count_sprites)
	{
		sp_order[i] = i;
		sp_dis[i] = ((cub->player.pos_x - cub->sprites[i].x) *
					(cub->player.pos_x - cub->sprites[i].x) +
					(cub->player.pos_y - cub->sprites[i].y) *
					(cub->player.pos_y - cub->sprites[i].y));
	}
	sort_sprites(sp_order, sp_dis, cub->count_sprites);
}

void	sp_draw(t_cub3d *cub, double *zbuf)
{
	int x;
	int y;
	int d;

	x = cub->draw.draw_start_x - 1;
	while (++x < cub->draw.draw_end_x)
	{
		y = cub->draw.draw_start_y - 1;
		cub->draw.tex_x = (int)(256 * (x - (-cub->draw.sprite_width / 2 +
		cub->draw.sprite_screen_x))
			* cub->text_s.width / cub->draw.sprite_width) / 256;
		if (cub->draw.transform_y > 0 && x > 0 &&
			x < cub->pars.s_width && cub->draw.transform_y < zbuf[x])
			while (++y < cub->draw.draw_end_y)
			{
				d = (y) * 256 - cub->pars.s_height * 128 +
				cub->draw.sprite_height * 128;
				cub->draw.tex_y = ((d * cub->text_s.height) /
				cub->draw.sprite_height) / 256;
				cub->draw.color = my_mlx_pixel_get(&cub->text_s,
											cub->draw.tex_x, cub->draw.tex_y);
				if ((cub->draw.color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&cub->canvas, x, y, cub->draw.color);
			}
	}
}
