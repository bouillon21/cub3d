/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshelli <cshelli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:50:44 by cshelli           #+#    #+#             */
/*   Updated: 2021/02/14 18:23:39 by cshelli          ###   ########.fr       */
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

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1920
#define screenHeight 1080
#define scale 30

typedef struct	s_canvas
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_canvas;

typedef struct s_player
{
  /*координаты игрока и скорость*/
  float posX;
  float posY;
  float speed;
  /*перемещение игрока*/
  int pres_w;
  int pres_a;
  int pres_s;
  int pres_d;

  double moveSpeed;
  double rotSpeed;
  int rot;
  // /*луч*/
  // float ray_start;
  // float ray_end;
  // float rot;

  float dirX;
  float dirY;

  float planeX;
  float planeY;

  double cameraX;
  double rayDirX;
  double rayDirY;

  int mapX;
  int mapY;

  double sideDistX;
  double sideDistY;

  double deltaDistX;
  double deltaDistY;
  double perpWallDist;

  float stepX;
  int stepY;
  int hit;
  int side;

  int drawStart;
  int drawEnd;
}               t_player;

typedef struct	s_map
{
	int			fd;
	char		**map;
}			t_map;

typedef struct s_point
{
  float x;
  float y;
}               t_point;

typedef struct cub3D
{
	t_map map;
	t_canvas canvas;
	t_player player;
	void	*mlx;
	void	*mlx_win;
}				t_cub3D;


void parser(t_map *map);
void	draw_square(const int x,const int y,int color, t_canvas *img);
void  draw_map(t_cub3D *cub ,int color);
void	my_mlx_pixel_put(t_canvas *data, int x, int y, int color);
void draw_player(t_cub3D *cub, int color);

void rotation_player(t_cub3D *cub);
void move_player(t_cub3D *cub);
int release_key(int keycode, t_cub3D *cub);
int press_key(int keycode, t_cub3D *cub);



#endif