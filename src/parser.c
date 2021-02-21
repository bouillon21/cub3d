/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:40 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/21 16:07:45 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map(t_cub3D *cub, t_list **head, int size)
{
	t_list	*tmp;
	char	*line;
	int		i;

	i = 0;
	tmp = *head;
	cub->pars.map = calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		cub->pars.map[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	valid_map(cub);
}

void	save_fc(t_cub3D *cub, char **mas, char flag)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(mas[1], ',');
	while (tmp[++i])
	{
		if (flag == 'F')
			cub->pars.F[i] = ft_atoi(tmp[i]);
		else
			cub->pars.C[i] = ft_atoi(tmp[i]);
	}
	free_array(cub, &tmp);
}

void	switch_(t_cub3D *cub, char **mas)
{
	if (mas[0] && !mas[3] && !cub->pars.sHeight && !ft_strncmp(mas[0], "R", 2))
		valid_screen_size(cub, mas);
	else if (mas[0] && !mas[2] && !cub->pars.NO && !ft_strncmp(mas[0], "NO", 3))
		cub->pars.NO = ft_strdup(mas[1]);
	else if (mas[0] && !mas[2] && !cub->pars.SO && !ft_strncmp(mas[0], "SO", 3))
		cub->pars.SO = ft_strdup(mas[1]);
	else if (mas[0] && !mas[2] && !cub->pars.WE && !ft_strncmp(mas[0], "WE", 3))
		cub->pars.WE = ft_strdup(mas[1]);
	else if (mas[0] && !mas[2] && !cub->pars.EA && !ft_strncmp(mas[0], "EA", 3))
		cub->pars.EA = ft_strdup(mas[1]);
	else if (mas[0] && !mas[2] && !cub->pars.S && !ft_strncmp(mas[0], "S", 2))
		cub->pars.S = ft_strdup(mas[1]);
	else if (mas[0] && !cub->pars.F[0] && !ft_strncmp(mas[0], "F", 2))
		save_fc(cub, mas, 'F');
	else if (mas[0] && !cub->pars.C[0] && !ft_strncmp(mas[0], "C", 2))
		save_fc(cub, mas, 'C');
	else if (mas[0])
		error_message("anvalid param");
}

void	parser(t_cub3D *cub)
{
	char	*line;
	char	**mas;
	t_list	*head;

	head = NULL;
	line = NULL;
	while (get_next_line(cub->pars.fd, &line))
	{
		if (line[0] != '1' && !check_one(line))
		{
			mas = ft_split(line, ' ');
			switch_(cub, mas);
			free_array(cub, &mas);
		}
		else
		{
			ft_lstadd_back(&head, ft_lstnew(line));
			while (get_next_line(cub->pars.fd, &line))
				ft_lstadd_back(&head, ft_lstnew(line));
			ft_lstadd_back(&head, ft_lstnew(line));
			break ;
		}
		free(line);
	}
	map(cub, &head, ft_lstsize(head));
	// while (1)
	// {}
}
