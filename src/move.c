/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:40:57 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/09 11:52:26 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		press_key(int keycode, t_cub3D *cub)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 2)
		cub->player.pres_d = 1;
	else if (keycode == 1)
		cub->player.pres_s = 1;
	else if (keycode == 0)
		cub->player.pres_a = 1;
	else if (keycode == 13)
		cub->player.pres_w = 1;
	if (keycode == 124)
		cub->player.rot = -1;
	else if (keycode == 123)
		cub->player.rot = 1;
	return (1);
}

int		release_key(int keycode, t_cub3D *cub)
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
	return (1);
}

void	move_da(t_cub3D *cub)
{
	if (cub->player.pres_a)
	{
		if (cub->pars.map[(int)(cub->player.posX - cub->player.planeX
			* cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.planeX * cub->player.moveSpeed;
		if (cub->pars.map[(int)(cub->player.posX)][(int)(cub->player.posY
			- cub->player.planeY * cub->player.moveSpeed)] == '0')
			cub->player.posY -= cub->player.planeY * cub->player.moveSpeed;
	}
	if (cub->player.pres_d)
	{
		if (cub->pars.map[(int)(cub->player.posX + cub->player.planeX
			* cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.planeX * cub->player.moveSpeed;
		if (cub->pars.map[(int)(cub->player.posX)][(int)(cub->player.posY
			+ cub->player.planeY * cub->player.moveSpeed)] == '0')
			cub->player.posY += cub->player.planeY * cub->player.moveSpeed;
	}
}

void	move_player(t_cub3D *cub)
{
	if (cub->player.pres_w)
	{
		if (cub->pars.map[(int)(cub->player.posX + cub->player.dirX
			* cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.dirX * cub->player.moveSpeed;
		if (cub->pars.map[(int)(cub->player.posX)][(int)(cub->player.posY
			+ cub->player.dirY * cub->player.moveSpeed)] == '0')
			cub->player.posY += cub->player.dirY * cub->player.moveSpeed;
	}
	if (cub->player.pres_s)
	{
		if (cub->pars.map[(int)(cub->player.posX - cub->player.dirX
			* cub->player.moveSpeed)][(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.dirX * cub->player.moveSpeed;
		if (cub->pars.map[(int)(cub->player.posX)][(int)(cub->player.posY
			- cub->player.dirY * cub->player.moveSpeed)] == '0')
			cub->player.posY -= cub->player.dirY * cub->player.moveSpeed;
	}
	move_da(cub);
}

void	rotation_player(t_cub3D *cub)
{
	float	old_dirx;
	float	oldlanex;
	float	rot_speed;

	old_dirx = cub->player.dirX;
	oldlanex = cub->player.planeX;
	rot_speed = cub->player.rot_speed * cub->player.rot;
	cub->player.dirX = cub->player.dirX * cos(rot_speed)
		- cub->player.dirY * sin(rot_speed);
	cub->player.dirY = old_dirx * sin(rot_speed)
		+ cub->player.dirY * cos(rot_speed);
	cub->player.planeX = cub->player.planeX * cos(rot_speed)
		- cub->player.planeY * sin(rot_speed);
	cub->player.planeY = oldlanex * sin(rot_speed)
		+ cub->player.planeY * cos(rot_speed);
}
