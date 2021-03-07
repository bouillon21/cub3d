/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:21:32 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/07 17:37:20 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	sum_sprites(t_cub3D *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->pars.map[++i])
	{
		j = -1;
		while (cub->pars.map[i][++j])
		{
			if (cub->pars.map[i][j] == '2')
				cub->count_sprites++;
		}
	}
	cub->sprites = malloc(sizeof(t_sprite *) * cub->count_sprites);
	if (!cub->sprites)
		error_message("malloc");
}

void	check_valid(char **map, int i, int j)
{
	if (i < 1 || j < 1)
		error_message("map");
	if (!map[i][j + 1] || !ft_strchr("012NSWE", map[i][j + 1]))
		error_message("map");
	if (!ft_strchr("012NSWE", map[i][j - 1]))
		error_message("map");
	if (!ft_strchr("012NSWE", map[i + 1][j]))
		error_message("map");
	if (!ft_strchr("012NSWE", map[i - 1][j]))
		error_message("map");
	if (!map[i + 1][j + 1] || !ft_strchr("012NSWE", map[i + 1][j + 1]))
		error_message("map");
	if (!map[i - 1][j + 1] || !ft_strchr("012NSWE", map[i - 1][j + 1]))
		error_message("map");
	if (!ft_strchr("012NSWE", map[i + 1][j - 1]))
		error_message("map");
	if (!ft_strchr("012NSWE", map[i - 1][j - 1]))
		error_message("map");
}

void	dir_player(t_cub3D *cub, char dir)
{
	if (dir == 'N')
	{
		cub->player.dirX = -1;
		cub->player.planeY = 0.66;
	}
	if (dir == 'S')
	{
		cub->player.dirX = 1;
		cub->player.planeY = -0.66;
	}
	if (dir == 'W')
	{
		cub->player.dirY = -1;
		cub->player.planeX = -0.66;
	}
	if (dir == 'E')
	{
		cub->player.dirY = 1;
		cub->player.planeX = 0.66;
	}
}

void	pos_player_sprite(t_cub3D *cub, char **map, int i, int j)
{
	static int	count;

	if (!count)
		count = 0;
	if (ft_strchr("NEWS", cub->pars.map[i][j]))
	{
		if (cub->player.posX != -1)
			error_message("many players");
		dir_player(cub, cub->pars.map[i][j]);
		cub->pars.map[i][j] = '0';
		cub->player.posX = i + 0.5;
		cub->player.posY = j + 0.5;
	}
	if (cub->pars.map[i][j] == '2')
	{
		cub->sprites[count].x = i + 0.5;
		cub->sprites[count].y = j + 0.5;
		count++;
	}
}

void	valid_map(t_cub3D *cub)
{
	int	i;
	int	j;

	i = -1;
	sum_sprites(cub);
	while (cub->pars.map[++i])
	{
		if (cub->pars.map[i][0] == '\0')
			error_message("map");
		j = -1;
		while (cub->pars.map[i][++j])
		{
			if (ft_strchr("02NEWS", cub->pars.map[i][j]))
				check_valid(cub->pars.map, i, j);
			pos_player_sprite(cub, cub->pars.map, i, j);
			if (!ft_strchr("012NEWS ", cub->pars.map[i][j]))
				error_message("map");
		}
	}
	if (cub->player.posX == -1)
		error_message("no player");
}
