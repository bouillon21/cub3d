/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:50:44 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/04 15:02:57 by cshelli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct	s_canvas
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_canvas;

typedef struct	s_sprite
{
	float		x;
	float		y;
}				t_sprite;

typedef struct	s_player
{
	/*координаты игрока*/
	float		posX;
	float		posY;
	/*направление игрока*/
	float		dirX;
	float		dirY;
	/*плоскость игрока игрока*/
	float		planeX;
	float		planeY;
	/*перемещение игрока*/
	int			pres_w;
	int			pres_a;
	int			pres_s;
	int			pres_d;
	/*скорости движения и поворота*/
	float		speed;
	double		moveSpeed;
	double		rotSpeed;
	int			rot;
}				t_player;

typedef struct	s_draw
{
	double		camX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	double		wallX;
	double		step;
	double		texPos;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			texX;
	int			texY;
	int			color;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;

	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			drawStartY;
	int			drawStartX;
	int			drawEndY;
	int			drawEndX;
	int			spriteWidth;
	int			stripe;
}				t_draw;

typedef struct	s_pars
{
	int			fd;
	int			sWidth;
	int			sHeight;
	int			F[3];
	int			C[3];
	char		**map;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
}				t_pars;

typedef struct	cub3D
{
	t_pars		pars;
	t_draw		draw;
	t_player	player;
	t_canvas	canvas;
	t_canvas	textNO;
	t_canvas	textSO;
	t_canvas	textWE;
	t_canvas	textEA;
	t_canvas	textS;
	t_sprite	*sprites;
	int			count_sprites;
}				t_cub3D;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

void	parser(t_cub3D *cub);
void	draw_square(const int x,const int y,int color, t_canvas *img);
void	draw_map(t_cub3D *cub ,int color);
void	my_mlx_pixel_put(t_canvas *data, int x, int y, int color);
int		my_mlx_pixel_get(t_canvas *texture, int x, int y);
void	draw_player(t_cub3D *cub, int color);

void	rotation_player(t_cub3D *cub);
void	move_player(t_cub3D *cub);
int		release_key(int keycode, t_cub3D *cub);
int		press_key(int keycode, t_cub3D *cub);

int		check_one(char *line);
void	free_array(t_cub3D *cub, char ***mas);
void	error_message(char *str);

void	cub_init(t_cub3D *cub);
void	init_texture(t_canvas *texture, char *way);
void	valid_screen_size(t_cub3D *cub, char **mas);
void	valid_init_texture(t_canvas *texture, char **way, char **mas);
void	valid_map(t_cub3D *cub);
void	valid_fc(int *pars, char **mas);
void	save_fc(t_cub3D *cub, char **mas, char flag);


void	step_side(t_draw *draw, t_player *player);
void	dda(t_draw *draw, char **map);
void	fish_eye__height_wall(t_draw *draw, t_player *player, int sheight);
void	tex_size(t_draw *draw, int width, int height);
void	draw_wall(t_cub3D *cub, int x, int y);
void	init_ray(t_cub3D *cub, int x );
void	texture(t_cub3D *cub);
void	draw_skye_floor(t_cub3D *cub, int x);

void	sp_post_dist(t_cub3D *cub, int i, int *sporder);
void	sp_height_width(t_draw *draw, t_pars *pars);
void	sp_draw(t_cub3D *cub, double *zbuf);
void	sp_sort_dist(t_cub3D *cub, int *sp_order, double *sp_dis);
void	sort_sprites(int *order, double *dist, int amount);
void	sort_order(t_pair *orders, int amount);

#endif