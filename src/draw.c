/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:20:09 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/07 17:48:08 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	draw_wall(t_cub3D *cub, int x, int y)
{
	while (++y < cub->draw.drawEnd)
	{
		cub->draw.texY = (int)cub->draw.texPos;
		cub->draw.texPos += cub->draw.step;
		if (cub->draw.side == 1)
		{
			if (cub->draw.stepY > 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textEA,
					cub->draw.texX, cub->draw.texY);
			else if (cub->draw.stepY < 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textWE,
					cub->draw.texX, cub->draw.texY);
		}
		else
		{
			if (cub->draw.stepX > 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textNO,
					cub->draw.texX, cub->draw.texY);
			else if (cub->draw.stepX < 0)
				cub->draw.color = my_mlx_pixel_get(&cub->textSO,
					cub->draw.texX, cub->draw.texY);
		}
		my_mlx_pixel_put(&cub->canvas, x, y, cub->draw.color);
	}
}

int		trgb(int mas[3])
{
	return (mas[0] << 16 | mas[1] << 8 | mas[2]);
}

void	draw_skye_floor(t_cub3D *cub, int x)
{
	int y;

	y = -1;
	while (++y < cub->draw.drawStart)
		my_mlx_pixel_put(&cub->canvas, x, y, trgb(cub->pars.C));
	y = cub->draw.drawEnd - 1;
	while (++y < cub->pars.sHeight - 1)
		my_mlx_pixel_put(&cub->canvas, x, y, trgb(cub->pars.F));
}
