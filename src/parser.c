/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:40 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:55:31 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map(t_cub3d *cub, t_list **head, int size)
{
	t_list	*tmp;
	char	*line;
	int		i;

	i = 0;
	tmp = *head;
	if (size < 1)
		error_message("map");
	cub->pars.map = calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		cub->pars.map[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	valid_map(cub);
	ft_lstclear(head, free);
}

void	switch_param(t_cub3d *cub, char **mas, int *sum)
{
	if (mas[0] && mas[1] && mas[2] && !mas[3] && !ft_strncmp(mas[0], "R", 2)
		&& !cub->pars.s_height)
		valid_screen_size(cub, mas, sum);
	else if (check_mas(mas) && !ft_strncmp(mas[0], "NO", 3) && !cub->pars.no)
		valid_init_texture(&cub->text_no, &cub->pars.no, mas, sum);
	else if (check_mas(mas) && !ft_strncmp(mas[0], "SO", 3) && !cub->pars.so)
		valid_init_texture(&cub->text_so, &cub->pars.so, mas, sum);
	else if (check_mas(mas) && !ft_strncmp(mas[0], "WE", 3) && !cub->pars.we)
		valid_init_texture(&cub->text_we, &cub->pars.we, mas, sum);
	else if (check_mas(mas) && !ft_strncmp(mas[0], "EA", 3) && !cub->pars.ea)
		valid_init_texture(&cub->text_ea, &cub->pars.ea, mas, sum);
	else if (check_mas(mas) && !ft_strncmp(mas[0], "S", 2) && !cub->pars.s)
		valid_init_texture(&cub->text_s, &cub->pars.s, mas, sum);
	else if (check_mas(mas) && !ft_strncmp(mas[0], "F", 2) && !cub->pars.f[0])
		valid_fc(cub->pars.f, mas, sum);
	else if (check_mas(mas) && !ft_strncmp(mas[0], "C", 2) && !cub->pars.c[0])
		valid_fc(cub->pars.c, mas, sum);
	else if (mas[0])
		error_message("anvalid param");
}

void	parser_map(t_list **head, char *line, int fd)
{
	ft_lstadd_back(head, ft_lstnew(line));
	while (get_next_line(fd, &line))
		ft_lstadd_back(head, ft_lstnew(line));
	ft_lstadd_back(head, ft_lstnew(line));
}

void	parser(t_cub3d *cub)
{
	char		*line;
	char		**mas;
	t_list		*head;
	static int	sum;

	line = NULL;
	while (get_next_line(cub->pars.fd, &line))
	{
		if (line[0] != '1' && !check_one(line))
		{
			mas = ft_split(line, ' ');
			switch_param(cub, mas, &sum);
			free_array(cub, &mas);
		}
		else
		{
			parser_map(&head, line, cub->pars.fd);
			break ;
		}
		free(line);
	}
	if (sum != 8)
		error_message("the number of arguments does not match");
	map(cub, &head, ft_lstsize(head));
	free(head);
}
