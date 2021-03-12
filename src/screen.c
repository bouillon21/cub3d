/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:18:18 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 10:26:11 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_screen(t_cub3d *all, int fd)
{
	int		size_screen;
	int		pos_pixel_data;
	int		zero;
	short	plane;

	plane = 1;
	zero = 0;
	pos_pixel_data = 54;
	size_screen = all->pars.s_height * all->pars.s_width * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pixel_data, 4);
	pos_pixel_data = 40;
	write(fd, &pos_pixel_data, 4);
	write(fd, &all->pars.s_width, 4);
	write(fd, &all->pars.s_height, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

static void	filling_file_screen(t_cub3d *all, int fd)
{
	int	i;
	int	j;
	int	color;

	i = all->pars.s_height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < all->pars.s_width)
		{
			color = *(int*)(all->canvas.addr + (i * all->canvas.line_length
					+ j * (all->canvas.bits_per_pixel / 8)));
			write(fd, &color, 4);
		}
	}
}

void		screenshot(t_cub3d *all)
{
	int fd;
	int size_screen;
	int zero;
	int size;

	if ((fd = open("screen.bmp", O_CREAT | O_RDWR, 0666)) < 0)
		error_message("screen");
	size_screen = all->pars.s_height * all->pars.s_width * 4 + 54;
	zero = 0;
	size = all->pars.s_height * all->pars.s_width;
	create_screen(all, fd);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	size_screen = 1000;
	write(fd, &size_screen, 4);
	write(fd, &size_screen, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	filling_file_screen(all, fd);
	close(fd);
	exit(0);
}
