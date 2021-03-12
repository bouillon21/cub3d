/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:13:49 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:57:31 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_cub3d *cub)
{
	int		x;
	int		sprite_order[cub->count_sprites];
	double	zbuffer[cub->pars.s_width];
	double	sprite_distance[cub->count_sprites];

	x = -1;
	while (++x < cub->pars.s_width)
	{
		init_ray(cub, x);
		step_side(&cub->draw, &cub->player);
		dda(&cub->draw, cub->pars.map);
		fish_eye__height_wall(&cub->draw, &cub->player, cub->pars.s_height);
		texture(cub);
		draw_wall(cub, x, cub->draw.draw_start - 1);
		draw_skye_floor(cub, x);
		zbuffer[x] = cub->draw.perp_wall_dist;
	}
	sp_sort_dist(cub, sprite_order, sprite_distance);
	x = -1;
	while (++x < cub->count_sprites)
	{
		sp_post_dist(cub, x, sprite_order);
		sp_height_width(&cub->draw, &cub->pars);
		sp_draw(cub, zbuffer);
	}
}

int		draw_img(t_cub3d *cub)
{
	move_player(cub);
	rotation_player(cub);
	render(cub);
	if (cub->screen)
		screenshot(cub);
	mlx_clear_window(cub->canvas.mlx, cub->canvas.mlx_win);
	mlx_put_image_to_window(cub->canvas.mlx, cub->canvas.mlx_win,
							cub->canvas.img, 0, 0);
	return (1);
}

void	valid_arg(t_cub3d *cub, int argc, char **argv)
{
	int	i;

	i = ft_strlen(argv[1]);
	if (argc < 2 || argc > 3)
		error_message("number of arguments");
	if (i < 4 || ft_strncmp(&argv[1][i - 4], ".cub", 4))
		error_message("config file");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		error_message("screen");
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		cub->screen = 1;
}

int		main(int argc, char **argv)
{
	t_cub3d	cub;

	valid_arg(&cub, argc, argv);
	cub.pars.fd = open(argv[1], O_RDONLY);
	cub_init(&cub);
	parser(&cub);
	cub.canvas.mlx = mlx_init();
	cub.canvas.img = mlx_new_image(cub.canvas.mlx, cub.pars.s_width,
		cub.pars.s_height);
	cub.canvas.addr = mlx_get_data_addr(cub.canvas.img,
		&cub.canvas.bits_per_pixel, &cub.canvas.line_length,
			&cub.canvas.endian);
	if (!cub.screen)
	{
		cub.canvas.mlx_win = mlx_new_window(cub.canvas.mlx, cub.pars.s_width,
		cub.pars.s_height, "Hi");
		mlx_hook(cub.canvas.mlx_win, 2, 1L << 0, &press_key, &cub);
		mlx_hook(cub.canvas.mlx_win, 3, 1L << 1, &release_key, &cub);
		mlx_hook(cub.canvas.mlx_win, 17, 1L << 0, &quit, &cub);
	}
	mlx_loop_hook(cub.canvas.mlx, &draw_img, &cub);
	mlx_loop(cub.canvas.mlx);
}
