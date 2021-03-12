/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:40:57 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:39:19 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		press_key(int keycode, t_cub3d *cub)
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

int		release_key(int keycode, t_cub3d *cub)
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

void	move_da(t_cub3d *cub)
{
	if (cub->player.pres_a)
	{
		if (cub->pars.map[(int)(cub->player.pos_x - cub->player.plane_x
			* cub->player.move_speed)][(int)(cub->player.pos_y)] == '0')
			cub->player.pos_x -= cub->player.plane_x * cub->player.move_speed;
		if (cub->pars.map[(int)(cub->player.pos_x)][(int)(cub->player.pos_y
			- cub->player.plane_y * cub->player.move_speed)] == '0')
			cub->player.pos_y -= cub->player.plane_y * cub->player.move_speed;
	}
	if (cub->player.pres_d)
	{
		if (cub->pars.map[(int)(cub->player.pos_x + cub->player.plane_x
			* cub->player.move_speed)][(int)(cub->player.pos_y)] == '0')
			cub->player.pos_x += cub->player.plane_x * cub->player.move_speed;
		if (cub->pars.map[(int)(cub->player.pos_x)][(int)(cub->player.pos_y
			+ cub->player.plane_y * cub->player.move_speed)] == '0')
			cub->player.pos_y += cub->player.plane_y * cub->player.move_speed;
	}
}

void	move_player(t_cub3d *cub)
{
	if (cub->player.pres_w)
	{
		if (cub->pars.map[(int)(cub->player.pos_x + cub->player.dir_x
			* cub->player.move_speed)][(int)(cub->player.pos_y)] == '0')
			cub->player.pos_x += cub->player.dir_x * cub->player.move_speed;
		if (cub->pars.map[(int)(cub->player.pos_x)][(int)(cub->player.pos_y
			+ cub->player.dir_y * cub->player.move_speed)] == '0')
			cub->player.pos_y += cub->player.dir_y * cub->player.move_speed;
	}
	if (cub->player.pres_s)
	{
		if (cub->pars.map[(int)(cub->player.pos_x - cub->player.dir_x
			* cub->player.move_speed)][(int)(cub->player.pos_y)] == '0')
			cub->player.pos_x -= cub->player.dir_x * cub->player.move_speed;
		if (cub->pars.map[(int)(cub->player.pos_x)][(int)(cub->player.pos_y
			- cub->player.dir_y * cub->player.move_speed)] == '0')
			cub->player.pos_y -= cub->player.dir_y * cub->player.move_speed;
	}
	move_da(cub);
}

void	rotation_player(t_cub3d *cub)
{
	float	old_dirx;
	float	oldlanex;
	float	rot_speed;

	old_dirx = cub->player.dir_x;
	oldlanex = cub->player.plane_x;
	rot_speed = cub->player.rot_speed * cub->player.rot;
	cub->player.dir_x = cub->player.dir_x * cos(rot_speed)
		- cub->player.dir_y * sin(rot_speed);
	cub->player.dir_y = old_dirx * sin(rot_speed)
		+ cub->player.dir_y * cos(rot_speed);
	cub->player.plane_x = cub->player.plane_x * cos(rot_speed)
		- cub->player.plane_y * sin(rot_speed);
	cub->player.plane_y = oldlanex * sin(rot_speed)
		+ cub->player.plane_y * cos(rot_speed);
}
