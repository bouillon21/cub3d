/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:40:57 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/14 18:40:12 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int press_key(int keycode, t_cub3D *cub)
{
	if (keycode == 53)
		exit (0);
	else if (keycode == 2)
		cub->player.pres_d = 1;
	else if (keycode == 1)
		cub->player.pres_s = 1;
	else if (keycode == 0)
		cub->player.pres_a = 1;
	else if (keycode == 13)
		cub->player.pres_w = 1;

	if(keycode == 124)
		cub->player.rot = -1;
	else if(keycode == 123)
		cub->player.rot = 1;
}

int release_key(int keycode, t_cub3D *cub)
{
	if (keycode == 2)
		cub->player.pres_d = 0;
	else if (keycode == 1)
		cub->player.pres_s = 0;
	else if (keycode == 0)
		cub->player.pres_a = 0;
	else if (keycode == 13)
		cub->player.pres_w = 0;
	else if (keycode == 123 || keycode == 124)
		cub->player.rot = 0;
}

void move_player(t_cub3D *cub)
{
	if (cub->player.pres_w)
	{
		if(cub->map.map[(int)(cub->player.posX + cub->player.dirX * cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.dirX * cub->player.moveSpeed;
		if(cub->map.map[(int)(cub->player.posX)][(int)(cub->player.posY + cub->player.dirY * cub->player.moveSpeed)] == '0')
			cub->player.posY += cub->player.dirY * cub->player.moveSpeed;
	}
	if (cub->player.pres_s)
	{
		if(cub->map.map[(int)(cub->player.posX - cub->player.dirX * cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.dirX * cub->player.moveSpeed;
		if(cub->map.map[(int)(cub->player.posX)][(int)(cub->player.posY - cub->player.dirY * cub->player.moveSpeed)] == '0')
			cub->player.posY -= cub->player.dirY * cub->player.moveSpeed;
	}
	if (cub->player.pres_a)
	{
		if(cub->map.map[(int)(cub->player.posX - cub->player.planeX * cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.planeX * cub->player.moveSpeed;
		if(cub->map.map[(int)(cub->player.posX)][(int)(cub->player.posY - cub->player.planeY * cub->player.moveSpeed)] == '0')
			cub->player.posY -= cub->player.planeY * cub->player.moveSpeed;
	}
	if (cub->player.pres_d)
	{
		if(cub->map.map[(int)(cub->player.posX + cub->player.planeX * cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.planeX * cub->player.moveSpeed;
		if(cub->map.map[(int)(cub->player.posX)][(int)(cub->player.posY + cub->player.planeY * cub->player.moveSpeed)] == '0')
			cub->player.posY += cub->player.planeY * cub->player.moveSpeed;
	}
}

void rotation_player(t_cub3D *cub)
{
	float oldDirX;
	float oldPlaneX;
	float rotSpeed;

	oldDirX = cub->player.dirX;
	oldPlaneX = cub->player.planeX;
	rotSpeed = cub->player.rotSpeed * cub->player.rot;
	cub->player.dirX = cub->player.dirX * cos(rotSpeed) - cub->player.dirY * sin(rotSpeed);
	cub->player.dirY = oldDirX * sin(rotSpeed) + cub->player.dirY * cos(rotSpeed);
	cub->player.planeX = cub->player.planeX * cos(rotSpeed) - cub->player.planeY * sin(rotSpeed);
	cub->player.planeY = oldPlaneX * sin(rotSpeed) + cub->player.planeY * cos(rotSpeed);
}