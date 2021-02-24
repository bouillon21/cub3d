/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:13:49 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/24 20:48:00 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
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
void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void raycast(t_cub3D *cub)
{
	int x;
	double ZBuffer[cub->pars.sWidth];

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
#pragma region //спрайты

//arrays used to sort the sprites
int spriteOrder[cub->count_sprites];
double spriteDistance[cub->count_sprites];
	for (int i = 0; i < cub->count_sprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((POS_X - cub->sprites[i].x) * (POS_X - cub->sprites[i].x) + (POS_Y - cub->sprites[i].y) * (POS_Y - cub->sprites[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, cub->count_sprites);

	//after sorting the sprites, do the projection and draw them
	for (int i = 0; i < cub->count_sprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = cub->sprites[spriteOrder[i]].x - POS_X;
		double spriteY = cub->sprites[spriteOrder[i]].y - POS_Y;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (PLANE_X * DIR_Y - DIR_X * PLANE_Y); //required for correct matrix multiplication

		double transformX = invDet * (DIR_Y * spriteX - DIR_X * spriteY);
		double transformY = invDet * (-PLANE_Y * spriteX + PLANE_X * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((cub->pars.sWidth / 2) * (1 + transformX / transformY));

//parameters for scaling and moving the sprites
//calculate height of the sprite on screen
      int spriteHeight = abs((int)(S_HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + S_HEIGHT / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + S_HEIGHT / 2;
      if(drawEndY >= S_HEIGHT) drawEndY = S_HEIGHT - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (S_HEIGHT / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= cub->pars.sWidth) drawEndX = cub->pars.sWidth - 1;

		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * cub->textS.width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < cub->pars.sWidth && transformY < ZBuffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - S_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					cub->draw.texY = ((d * cub->textS.height) / spriteHeight) / 256;
					cub->draw.color = my_mlx_pixel_get(&cub->textS, texX, cub->draw.texY);
					if ((cub->draw.color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(&cub->canvas, stripe, y, cub->draw.color);
				}
		}
	}
	#pragma endregion
}

int draw_img(t_cub3D * cub)
{
	mlx_clear_window(cub->canvas.mlx, cub->canvas.mlx_win);
	mlx_destroy_image(cub->canvas.mlx, cub->canvas.img);
	cub->canvas.img = mlx_new_image(cub->canvas.mlx, cub->pars.sWidth,S_HEIGHT);
	move_player(cub);
	rotation_player(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->canvas.mlx, cub->canvas.mlx_win,cub->canvas.img, 0, 0);
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