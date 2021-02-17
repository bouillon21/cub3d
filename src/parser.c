/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:40 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/17 20:52:44 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int size_file()
// {
// 	int fd;
// 	int size;
// 	char ch;

// 	size = 0;
// 	fd = open("map.txt", O_RDONLY);
// 	while (read(fd, &ch, 1) > 0)
// 	{
// 		if (ch == '\n')
// 			size++;
// 	}
// 	return(++size);
// }


// void parser(t_cub3D *cub)
// {
// 	int i;
// 	// char *line;
// 	// t_list *head;

// 	// head = NULL;
// 	// line = NULL;
// 	i = 0;
// 	cub->pars.map = calloc(size_file() + 1, sizeof(char *));
// 	cub->pars.fd = open("map.txt", O_RDONLY);
// 	while (get_next_line(cub->pars.fd, &cub->pars.map[i]))
// 		i++;
// 	// 	ft_lstadd_back(&head, ft_lstnew(line));
// 	// ft_lstadd_back(&head, ft_lstnew(line));
// }

void map(t_cub3D *cub, t_list **head, int size)
{
	// cub->map.map = calloc(size_file() + 1, sizeof(char *));
	t_list	*tmp;
	char	*line;
	int		i;

	tmp = *head;
	while (tmp)
	{
		i = 0;
		line = tmp->content;
			printf("%s", ft_strnstr(line, "NO", ft_strlen(line)));
		tmp = tmp->next;
	}
}

void free_array(t_cub3D *cub, char ***mas)
{
	int i;

	i = 0;
	while ((*mas)[i])
	{
		free((*mas)[i]);
		i++;
	}
	free(*mas);
}

void save_FC(t_cub3D *cub, char **mas, char flag)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(mas[1], ',');
	while (tmp[++i])
	{
		if(flag == 'F')
			cub->pars.F[i] = ft_atoi(tmp[i]);
		else
			cub->pars.C[i] = ft_atoi(tmp[i]);
	}
	free_array(cub, &tmp);
}

void switch_(t_cub3D *cub, char **mas)
{
	if (mas[0] && !ft_strncmp(mas[0],"R", 2))
	{
		cub->pars.sWidth = ft_atoi(mas[1]);
		cub->pars.sHeight = ft_atoi(mas[2]);
	}
	if (mas[0] && !ft_strncmp(mas[0],"NO", 3))
		cub->pars.NO = ft_strdup(mas[1]);
	if (mas[0] && !ft_strncmp(mas[0],"SO", 3))
		cub->pars.SO = ft_strdup(mas[1]);
	if (mas[0] && !ft_strncmp(mas[0],"WE", 3))
		cub->pars.WE = ft_strdup(mas[1]);
	if (mas[0] && !ft_strncmp(mas[0],"EA", 3))
		cub->pars.EA = ft_strdup(mas[1]);
	if (mas[0] && !ft_strncmp(mas[0],"S", 2))
		cub->pars.S = ft_strdup(mas[1]);
	if (mas[0] && !ft_strncmp(mas[0],"F", 2))
		save_FC(cub, mas, 'F');
	if (mas[0] && !ft_strncmp(mas[0],"C", 2))
		save_FC(cub, mas, 'C');
}


void parser(t_cub3D *cub)
{
	int		i;
	char	*line;
	char	**mas;
	t_list	*head;

	head = NULL;
	line = NULL;
	cub->pars.fd = open("map.txt",O_RDONLY);
	while (get_next_line(cub->pars.fd, &line))
	{
		mas = ft_split(line, ' ');
		switch_(cub, mas);
		free_array(cub, &mas);
		free(line);
	}
	// 	ft_lstadd_back(&head, ft_lstnew(line));
	// ft_lstadd_back(&head, ft_lstnew(line));
	// free(line);
	// map(cub, &head, ft_lstsize(head));
}
