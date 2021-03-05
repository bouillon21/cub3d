/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:35:40 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/05 20:48:29 by cshelli          ###   ########.fr       */
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

void err(t_cub3D *cub)
{
	printf("R: %d\t%d\n", cub->pars.sWidth,cub->pars.sHeight);
	printf("NO: %s\n", cub->pars.NO);
	printf("SO: %s\n", cub->pars.SO);
	printf("WE: %s\n", cub->pars.WE);
	printf("EA: %s\n", cub->pars.EA);
	printf("S: %s\n", cub->pars.S);
	printf("F: %d\t%d\t%d\n", cub->pars.F[0], cub->pars.F[1], cub->pars.F[2]);
	printf("C: %d\t%d\t%d\n", cub->pars.C[0], cub->pars.C[1], cub->pars.C[2]);
	error_message("anvalid param");
}

void	switch_param(t_cub3D *cub, char **mas)
{
	if (mas[0] && mas[1] && mas[2] && !ft_strncmp(mas[0], "R", 2)
		&& !cub->pars.sHeight)
		valid_screen_size(cub, mas);
	else if (mas[0] && mas[1] && !ft_strncmp(mas[0], "NO", 3)
		&& !mas[2] && !cub->pars.NO)
		valid_init_texture(&cub->textNO, &cub->pars.NO, mas);
	else if (mas[0] && mas[1] && !ft_strncmp(mas[0], "SO", 3)
		&& !mas[2] && !cub->pars.SO)
		valid_init_texture(&cub->textSO, &cub->pars.SO, mas);
	else if (mas[0] && mas[1] && !ft_strncmp(mas[0], "WE", 3)
		&& !mas[2] && !cub->pars.WE)
		valid_init_texture(&cub->textWE, &cub->pars.WE, mas);
	else if (mas[0] && mas[1] && !ft_strncmp(mas[0], "EA", 3)
		&& !mas[2] && !cub->pars.EA)
		valid_init_texture(&cub->textEA, &cub->pars.EA, mas);
	else if (mas[0] && mas[1] && !ft_strncmp(mas[0], "S", 2)
		&& !mas[2] && !cub->pars.S)
		valid_init_texture(&cub->textS, &cub->pars.S, mas);
	else if (mas[0] && mas[1] && !ft_strncmp(mas[0], "F", 2)
		&& !mas[2] && !cub->pars.F[0])
		valid_fc(cub->pars.F, mas);
	else if (mas[0] && mas[1] && !ft_strncmp(mas[0], "C", 2) 
		&& !mas[2] && !cub->pars.C[0])
		valid_fc(cub->pars.C, mas);
	else if (mas[0])
		error_message("anvalid param");
}

void	empty_check(t_pars *pars)
{
	
}

void	parser(t_cub3D *cub)
{
	char	*line;
	char	**mas;
	t_list	*head;

	// head = NULL;
	line = NULL;
	while (get_next_line(cub->pars.fd, &line))
	{
		if (line[0] != '1' && !check_one(line))
		{
			mas = ft_split(line, ' ');
			switch_param(cub, mas);
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
	empty_check(&cub->pars);
	map(cub, &head, ft_lstsize(head));
	ft_lstclear(&head, free);
	free(head);
	printf("R: %d\t%d\n", cub->pars.sWidth,cub->pars.sHeight);
	printf("NO: %s\n", cub->pars.NO);
	printf("SO: %s\n", cub->pars.SO);
	printf("WE: %s\n", cub->pars.WE);
	printf("EA: %s\n", cub->pars.EA);
	printf("S: %s\n", cub->pars.S);
	printf("F: %d\t%d\t%d\n", cub->pars.F[0], cub->pars.F[1], cub->pars.F[2]);
	printf("C: %d\t%d\t%d\n", cub->pars.C[0], cub->pars.C[1], cub->pars.C[2]);
	int i = -1;
	while (cub->pars.map[++i])
	{
		printf("%s\n", cub->pars.map[i]);
	}
}
