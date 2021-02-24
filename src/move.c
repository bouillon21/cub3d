/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:40:57 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/23 19:01:19 by cshelli          ###   ########.fr       */
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
	return(1);
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
	return(1);
}

void move_player(t_cub3D *cub)
{
	if (cub->player.pres_w)
	{
		if(cub->pars.map[(int)(POS_X + DIR_X * cub->player.moveSpeed)][(int)(POS_Y)] == '0')
			POS_X += DIR_X * cub->player.moveSpeed;
		if(cub->pars.map[(int)(POS_X)][(int)(POS_Y + DIR_Y * cub->player.moveSpeed)] == '0')
			POS_Y += DIR_Y * cub->player.moveSpeed;
	}
	if (cub->player.pres_s)
	{
		if(cub->pars.map[(int)(POS_X - DIR_X * cub->player.moveSpeed)][(int)(POS_Y)] == '0')
			POS_X -= DIR_X * cub->player.moveSpeed;
		if(cub->pars.map[(int)(POS_X)][(int)(POS_Y - DIR_Y * cub->player.moveSpeed)] == '0')
			POS_Y -= DIR_Y * cub->player.moveSpeed;
	}
	if (cub->player.pres_a)
	{
		if(cub->pars.map[(int)(POS_X - PLANE_X * cub->player.moveSpeed)][(int)(POS_Y)] == '0')
			POS_X -= PLANE_X * cub->player.moveSpeed;
		if(cub->pars.map[(int)(POS_X)][(int)(POS_Y - PLANE_Y * cub->player.moveSpeed)] == '0')
			POS_Y -= PLANE_Y * cub->player.moveSpeed;
	}
	if (cub->player.pres_d)
	{
		if(cub->pars.map[(int)(POS_X + PLANE_X * cub->player.moveSpeed)][(int)(POS_Y)] == '0')
			POS_X += PLANE_X * cub->player.moveSpeed;
		if(cub->pars.map[(int)(POS_X)][(int)(POS_Y + PLANE_Y * cub->player.moveSpeed)] == '0')
			POS_Y += PLANE_Y * cub->player.moveSpeed;
	}
}

void rotation_player(t_cub3D *cub)
{
	float oldDirX;
	float oldPlaneX;
	float rotSpeed;

	oldDirX = DIR_X;
	oldPlaneX = PLANE_X;
	rotSpeed = cub->player.rotSpeed * cub->player.rot;
	DIR_X = DIR_X * cos(rotSpeed) - DIR_Y * sin(rotSpeed);
	DIR_Y = oldDirX * sin(rotSpeed) + DIR_Y * cos(rotSpeed);
	PLANE_X = PLANE_X * cos(rotSpeed) - PLANE_Y * sin(rotSpeed);
	PLANE_Y = oldPlaneX * sin(rotSpeed) + PLANE_Y * cos(rotSpeed);
}