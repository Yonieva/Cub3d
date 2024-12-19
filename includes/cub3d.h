/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:09:08 by yonieva           #+#    #+#             */
/*   Updated: 2024/10/13 16:09:08 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/********************************INCLUDES******************************/
# include "colors.h"
# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
/*********************************************************************/
/********************************DEFINES******************************/

typedef unsigned long	t_ulong;

//define WIN_WIDTH 960 640
//define WIN_HEIGHT 600 480
# define WIN_WIDTH 960
# define WIN_HEIGHT 600

# define TEX_SIZE 64

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# ifndef BONUS
#  define BONUS 1
# endif

# define MOVESPEED 0.0325
# define ROTSPEED 0.015

# define DIST_EDGE_MOUSE_WRAP 20

//Floor et ceiling bonus
#define FLOOR_TEXTURE_INDEX 14
#define CEILING_TEXTURE_INDEX 15

//minimap
# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040
# define MMAP_COLOR_DOOR 0xFFFF00

//error msg
# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"
/*********************************************************************/
/*****************************ENUMS***********************************/
enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
	DOOR = 4,
	SKULL = 5,
	LIB1 = 6,
	LIB2 = 7,
	SECRET = 8,
	WBASE = 9,
	WBLOOD = 10,
	WDARK = 11,
	WPAINT = 12,
	WRED = 13,
	TFLOOR = 14,
	TCEILING = 15
};

/*********************************************************************/
/*****************************STRUCTURES******************************/
typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor_texture;
	char			*ceiling_texture;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_minimap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
}	t_minimap;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_door
{
	int pos_x;
	int pos_y;
	int is_open;
}	t_door;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_mapinfo	mapinfo;
	char		**map;
	t_door		door;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_texinfo	texinfo;
	t_img		minimap;
	int			start_game;
	void		*title_img;
}	t_data;
/*********************************************************************/
/********************************FONCTIONS****************************/
/*********************************************************************/
void	print_controls(void);
void	draw_title_screen(t_data *data);
void	play_intro_video(t_data *data);
//*********************************init
void	init_data(t_data *data);
void	init_img_clean(t_img *img);
void	init_ray(t_ray *ray);
void	init_mlx(t_data *data);
void	init_texture_img(t_data *data, t_img *image, char *path);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_texinfo(t_texinfo *textures);
void	init_textures(t_data *data);
void	init_door(t_data *data);
void	init_title_screen(t_data *data);
int		*xpm_to_img(t_data *data, char *path);
//*********************************parsing
int		parse_args(t_data *data, char **av);
int		check_file(char *arg, bool cub);
void	parse_data(char *path, t_data *data);
int		get_file_data(t_data *data, char **map);
int		check_map_validity(t_data *data, char **map_tab);
int		check_map_sides(t_mapinfo *map, char **map_tab);
int		check_textures_validity(t_data *data, t_texinfo *textures);
char	*get_texture_path(char *line, int j);
int		fill_color(t_data *data, t_texinfo *textures, char *line, int j);
int		create_map(t_data *data, char **file, int i);
int		is_a_white_space(char c);
size_t	find_biggest_len(t_mapinfo *map, int i);
//*********************************movement
void	init_player_direction(t_data *data);
void	listen_for_input(t_data *data);
int		move_player(t_data *data);
int		validate_move(t_data *data, double new_x, double new_y);
int		rotate_player(t_data *data, double rotdir);
void	check_door(t_data *data);
//*********************************render
void	render_images(t_data *data);
int		render(t_data *data);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	init_texture_pixels(t_data *data);
void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x);
int		raycasting(t_player *player, t_data *data);
void	render_minimap(t_data *data);
void	render_minimap_image(t_data *data, t_minimap *minimap);
//*********************************exit/free
int		quit_cub3d(t_data *data);
void	clean_exit(t_data *data, int code);
void	free_tab(void **tab);
int		free_data(t_data *data);
int		err_msg_val(int detail, char *str, int code);
int		err_msg(char *detail, char *str, int code);

#endif
