/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:13:49 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/17 20:43:58 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init(t_cub3D *cub)
{
	cub->player.pres_w = 0;
	cub->player.pres_a = 0;
	cub->player.pres_s = 0;
	cub->player.pres_d = 0;

	cub->player.posX = 11;
	cub->player.posY = 2;
	cub->player.speed = 0.1;
	cub->player.moveSpeed = 0.4;
	cub->player.rotSpeed = 0.4;

	cub->player.dirX = -1;
	cub->player.dirY = 0;

	cub->player.planeX = 0;
	cub->player.planeY = 0.66;
	cub->player.rot = 0;
}

void raycast(t_cub3D *cub)
{
	int i;
  
	for(int x = 0; x < screenWidth; x++)
  {
    // calculate ray position and direction
      double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
      double rayDirX = cub->player.dirX + cub->player.planeX * cameraX;
      double rayDirY = cub->player.dirY + cub->player.planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)cub->player.posX;
      int mapY = (int)cub->player.posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

        //length of ray from one x or y-side to next x or y-side
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (cub->player.posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - cub->player.posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (cub->player.posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - cub->player.posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        // if(worldMap[mapX][mapY] > 0) hit = 1;
        if(cub->pars.map[mapX][mapY] != '0') hit = 1;

      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if(side == 0) 
          perpWallDist = (mapX - cub->player.posX + (1 - stepX) / 2) / rayDirX;
      else
          perpWallDist = (mapY - cub->player.posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(screenHeight / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenHeight / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + screenHeight / 2;
      if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;


//отрисовка
      int y;
      y = 0;
      while (y <= drawStart)
      {
        my_mlx_pixel_put(&cub->canvas,x ,y, 0x003b5eeb);
        y++;
      }
      while (y < drawEnd)
      {
        if (side == 1)
        {
          if(stepY > 0)
                my_mlx_pixel_put(&cub->canvas,x ,y, 0x0044F5A6);
          else if(stepY < 0)
                my_mlx_pixel_put(&cub->canvas,x ,y, 0x00FFFFFF);
        }
        else
        {
          if(stepX > 0)
                my_mlx_pixel_put(&cub->canvas,x ,y, 0x0082248f);
          else if(stepX < 0)
                my_mlx_pixel_put(&cub->canvas,x ,y, 0x00d95050);
        }
        y++;
      }
	}
}

int draw_img(t_cub3D *cub)
{
	mlx_clear_window(cub->mlx, cub->mlx_win);
	mlx_destroy_image(cub->mlx, cub->canvas.img);
	cub->canvas.img = mlx_new_image(cub->mlx, screenWidth, screenHeight);
  move_player(cub);
  rotation_player(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->canvas.img, 0, 0);
}

int main()
{
	t_cub3D cub;

	parser(&cub.pars);
	// #pragma region //init mlx
	// cub.mlx = mlx_init();
	// cub.mlx_win = mlx_new_window(cub.mlx, screenWidth, screenHeight, "Hi");
	// cub.canvas.img = mlx_new_image(cub.mlx, screenWidth, screenHeight);
	// cub.canvas.addr = mlx_get_data_addr(cub.canvas.img, &cub.canvas.bits_per_pixel, &cub.canvas.line_length, &cub.canvas.endian);
	// #pragma endregion
	// init(&cub);
	// mlx_hook(cub.mlx_win, 2, 1L<<0, &press_key, &cub);
	// mlx_hook(cub.mlx_win, 3, 1L<<1, &release_key, &cub);
	// mlx_loop_hook(cub.mlx, &draw_img, &cub);
	// mlx_loop(cub.mlx);
}