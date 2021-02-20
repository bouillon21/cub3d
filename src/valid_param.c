/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:39:30 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/20 18:30:26 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	valid_screen_size(t_cub3D *cub, char **mas)
{
	int i;

	i = -1;
	while (mas[1][++i])
		if (!ft_isdigit(mas[1][i]))
			error_message("scren size anvalid!");
	i = -1;
	while (mas[2][++i])
		if (!ft_isdigit(mas[2][i]))
			error_message("scren size anvalid!");
	if (ft_atoi(mas[1]) == 0 || ft_atoi(mas[2]) == 0)
		error_message("scren size anvalid!");
	cub->pars.sWidth = ft_atoi(mas[1]);
	cub->pars.sHeight = ft_atoi(mas[2]);
}

// void	valid_fc(t_cub3D *cub, char **mas, char param)
// {
// 	save_fc(cub, mas, param);
// }

// void	valid_save_texture(t_canvas *texture, t_pars *way, char **mas)
// {
// 	way->NO = ft_strdup(mas[1]);
// 	texture->mlx = mlx_init();
// 	if (!(texture->img = mlx_xpm_file_to_image(&texture->mlx, way->NO, &texture->width, &texture->height)))
// 		error_message("texture");
// 	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
// }