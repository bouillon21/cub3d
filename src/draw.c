/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:20:09 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:55:20 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_canvas *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		my_mlx_pixel_get(t_canvas *texture, int x, int y)
{
	char	*dst;
	int		color;

	dst = texture->addr + (y * texture->line_length + x
		* (texture->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	draw_wall(t_cub3d *cub, int x, int y)
{
	while (++y < cub->draw.draw_end)
	{
		cub->draw.tex_y = (int)cub->draw.tex_pos;
		cub->draw.tex_pos += cub->draw.step;
		if (cub->draw.side == 1)
		{
			if (cub->draw.step_y > 0)
				cub->draw.color = my_mlx_pixel_get(&cub->text_ea,
					cub->draw.tex_x, cub->draw.tex_y);
			else if (cub->draw.step_y < 0)
				cub->draw.color = my_mlx_pixel_get(&cub->text_we,
					cub->draw.tex_x, cub->draw.tex_y);
		}
		else
		{
			if (cub->draw.step_x > 0)
				cub->draw.color = my_mlx_pixel_get(&cub->text_no,
					cub->draw.tex_x, cub->draw.tex_y);
			else if (cub->draw.step_x < 0)
				cub->draw.color = my_mlx_pixel_get(&cub->text_so,
					cub->draw.tex_x, cub->draw.tex_y);
		}
		my_mlx_pixel_put(&cub->canvas, x, y, cub->draw.color);
	}
}

int		trgb(int mas[3])
{
	return (mas[0] << 16 | mas[1] << 8 | mas[2]);
}

void	draw_skye_floor(t_cub3d *cub, int x)
{
	int y;

	y = -1;
	while (++y < cub->draw.draw_start)
		my_mlx_pixel_put(&cub->canvas, x, y, trgb(cub->pars.c));
	y = cub->draw.draw_end - 1;
	while (++y < cub->pars.s_height - 1)
		my_mlx_pixel_put(&cub->canvas, x, y, trgb(cub->pars.f));
}
