/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:13:49 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/25 21:08:46 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	sort_order(t_pair *orders, int amount)
{
	int i;
	int j;
	t_pair	tmp;

	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}
void	sort_sprites(int *order, double *dist, int amount)
{
	int i;
	t_pair	*sprites;

	i = -1;
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	while(++i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	i = -1;
	while (++i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void	render(t_cub3D *cub)
{
	int x;
	int spriteOrder[cub->count_sprites];
	double ZBuffer[cub->pars.sWidth];
	double spriteDistance[cub->count_sprites];

	x = -1;
	while (++x < cub->pars.sWidth)
	{
		init_ray(cub, x);
		step_side(&cub->draw, &cub->player);
		dda(&cub->draw, cub->pars.map);//perform DDA
		fish_eye__height_wall(&cub->draw, &cub->player, cub->pars.sHeight);
		texture(cub);
		draw_wall(cub, x, cub->draw.drawStart - 1);
		draw_skye_floor(cub, x);
		ZBuffer[x] = cub->draw.perpWallDist; //perpendicular distance is used
	}
	sp_sort_dist(cub, spriteOrder,spriteDistance);
	x = -1;
	while (++x < cub->count_sprites)
	{
		sp_post_dist(cub, x, spriteOrder);
		sp_height_width(&cub->draw, &cub->pars);
		sp_draw(cub, ZBuffer);
	}
}

int draw_img(t_cub3D * cub)
{
	mlx_clear_window(cub->canvas.mlx, cub->canvas.mlx_win);
	mlx_destroy_image(cub->canvas.mlx, cub->canvas.img);
	cub->canvas.img = mlx_new_image(cub->canvas.mlx,
						cub->pars.sWidth,cub->pars.sHeight);
	move_player(cub);
	rotation_player(cub);
	render(cub);
	mlx_put_image_to_window(cub->canvas.mlx, cub->canvas.mlx_win,
							cub->canvas.img, 0, 0);
	return(1);
}

int main()
{
	t_cub3D cub;
	cub.pars.fd = open("map_ahegao.txt", O_RDONLY);
	parser(&cub);
	cub_init(&cub);
#pragma region //init mlx
	cub.canvas.mlx = mlx_init();
	cub.canvas.mlx_win = mlx_new_window(cub.canvas.mlx, cub.pars.sWidth, cub.pars.sHeight, "Hi");
	cub.canvas.img = mlx_new_image(cub.canvas.mlx, cub.pars.sWidth, cub.pars.sHeight);
	cub.canvas.addr = mlx_get_data_addr(cub.canvas.img, &cub.canvas.bits_per_pixel, &cub.canvas.line_length, &cub.canvas.endian);
#pragma endregion
	mlx_hook(cub.canvas.mlx_win, 2, 1L << 0, &press_key, &cub);
	mlx_hook(cub.canvas.mlx_win, 3, 1L << 1, &release_key, &cub);
	mlx_loop_hook(cub.canvas.mlx, &draw_img, &cub);
	mlx_loop(cub.canvas.mlx);
	}