/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:57:52 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/07 18:53:08 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_one(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

void	free_array(t_cub3D *cub, char ***mas)
{
	int	i;

	i = 0;
	while ((*mas)[i])
	{
		free((*mas)[i]);
		i++;
	}
	free(*mas);
}

void	error_message(char *str)
{
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	exit(0);
}

int		check_mas(char **mas)
{
	if (mas[0] && mas[1] && !mas[2])
		return (1);
	return (0);
}

int		quit(int keycode, t_cub3D *cub)
{
	(void) keycode;
	(void) cub;
	exit(0);
	return (1);
}
