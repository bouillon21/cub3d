/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:39:30 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/05 22:03:17 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	adapt_screen_size(t_cub3D *cub)
{
	int w;
	int h;

	mlx_get_screen_size(&w, &h);
	if (cub->pars.sWidth > w)
		cub->pars.sWidth = w;
	if (cub->pars.sHeight > h)
		cub->pars.sHeight = h;
}

void	valid_screen_size(t_cub3D *cub, char **mas)
{
	int i;

	i = -1;
	while (mas[1][++i])
	{
		if (!ft_isdigit(mas[1][i]))
			error_message("scren size anvalid!");
		cub->pars.sWidth = cub->pars.sWidth * 10 + (mas[1][i] - 48);
		if (cub->pars.sWidth > 999999)
			cub->pars.sWidth = 999999;
	}
	i = -1;
	while (mas[2][++i])
	{
		if (!ft_isdigit(mas[2][i]))
			error_message("scren size anvalid!");
		cub->pars.sHeight = cub->pars.sHeight * 10 + (mas[2][i] - 48);
		if (cub->pars.sHeight > 999999)
			cub->pars.sHeight = 999999;
	}
	adapt_screen_size(cub);
	if (cub->pars.sWidth == 0 || cub->pars.sHeight == 0)
		error_message("scren size anvalid!");
}

int		atoi_cub(char *mas, int *i, int *pars)
{
	*pars = 0;
	if (!ft_isdigit(mas[*i]))
		return (-1);
	while (ft_isdigit(mas[*i]))
	{
		*pars = *pars * 10 + (mas[*i] - 48);
		if (*pars > 255)
			return (-1);
		(*i)++;
	}
	return (1);
}

void	valid_fc(int *pars, char **mas)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		if (atoi_cub(mas[1], &i, &pars[j]) == -1)
			error_message("color");
		if ((mas[1][i] != ',' && mas[1][i] != '\0')
			|| mas[1][ft_strlen(mas[1]) - 1] == ',')
			error_message("color");
		i++;
		j++;
	}
}

void	valid_init_texture(t_canvas *texture, char **way, char **mas)
{
	*way = ft_strdup(mas[1]);
	texture->mlx = mlx_init();
	if (!(texture->img = mlx_xpm_file_to_image(&texture->mlx, *way, &texture->width, &texture->height)))
		error_message("texture");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
}