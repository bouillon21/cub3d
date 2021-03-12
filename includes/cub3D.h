/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:50:44 by cshelli           #+#    #+#             */
/*   Updated: 2021/03/12 09:55:34 by cshelli          ###   ########.fr       */
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
	float		pos_x;
	float		pos_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	int			pres_w;
	int			pres_a;
	int			pres_s;
	int			pres_d;
	float		speed;
	double		move_speed;
	double		rot_speed;
	int			rot;
}				t_player;

typedef struct	s_draw
{
	double		cam_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			tex_x;
	int			tex_y;
	int			color;
	int			line_height;
	int			draw_start;
	int			draw_end;

	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_start_x;
	int			draw_end_y;
	int			draw_end_x;
	int			sprite_width;
	int			stripe;
}				t_draw;

typedef struct	s_pars
{
	int			fd;
	int			s_width;
	int			s_height;
	int			f[3];
	int			c[3];
	char		**map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
}				t_pars;

typedef struct	s_cub3d
{
	t_pars		pars;
	t_draw		draw;
	t_player	player;
	t_canvas	canvas;
	t_canvas	text_no;
	t_canvas	text_so;
	t_canvas	text_we;
	t_canvas	text_ea;
	t_canvas	text_s;
	t_sprite	*sprites;
	int			count_sprites;
	int			screen;
}				t_cub3d;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

void			parser(t_cub3d *cub);
void			draw_square(const int x, const int y, int color, t_canvas *img);
void			draw_map(t_cub3d *cub, int color);
void			my_mlx_pixel_put(t_canvas *data, int x, int y, int color);
int				my_mlx_pixel_get(t_canvas *texture, int x, int y);
void			draw_player(t_cub3d *cub, int color);

void			rotation_player(t_cub3d *cub);
void			move_player(t_cub3d *cub);
int				release_key(int keycode, t_cub3d *cub);
int				press_key(int keycode, t_cub3d *cub);

int				check_one(char *line);
int				check_mas(char **mas);
void			free_array(t_cub3d *cub, char ***mas);
void			error_message(char *str);
int				quit(int keycode, t_cub3d *cub);

void			cub_init(t_cub3d *cub);
void			init_texture(t_canvas *texture, char *way);
void			valid_screen_size(t_cub3d *cub, char **mas, int *sum);
void			valid_init_texture(t_canvas *texture, char **way,
					char **mas, int *sum);
void			valid_map(t_cub3d *cub);
void			valid_fc(int *pars, char **mas, int *sum);
void			save_fc(t_cub3d *cub, char **mas, char flag);

void			step_side(t_draw *draw, t_player *player);
void			dda(t_draw *draw, char **map);
void			fish_eye__height_wall(t_draw *draw, t_player *player,
					int sheight);
void			tex_size(t_draw *draw, int width, int height);
void			draw_wall(t_cub3d *cub, int x, int y);
void			init_ray(t_cub3d *cub, int x);
void			texture(t_cub3d *cub);
void			draw_skye_floor(t_cub3d *cub, int x);

void			sort_order(t_pair *orders, int amount);
void			sort_sprites(int *order, double *dist, int amount);
void			sp_post_dist(t_cub3d *cub, int i, int *sporder);
void			sp_height_width(t_draw *draw, t_pars *pars);
void			sp_draw(t_cub3d *cub, double *zbuf);
void			sp_sort_dist(t_cub3d *cub, int *sp_order, double *sp_dis);
void			sort_sprites(int *order, double *dist, int amount);
void			sort_order(t_pair *orders, int amount);

void			screenshot(t_cub3d *all);

#endif
