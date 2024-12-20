/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:34:03 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/20 20:46:03 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*on copie les images et on destroy direct comme ca c est deja liberer*/
int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;
	/*Chargement de la texture stockée dans tmp temporairement.*/
	init_texture_img(data, &tmp, path);
	/*tableau qui contiendra tous les pixels de la texture*/
	buffer = ft_calloc(1,
			sizeof * buffer * data->texinfo.size * data->texinfo.size);
	if (!buffer)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	y = 0;
	/*Copie des pixels de tmp a buffer*/
	while (y < data->texinfo.size)
	{
		x = 0;
		while (x < data->texinfo.size)
		{
			buffer[y * data->texinfo.size + x]
				= tmp.addr[y * data->texinfo.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

static void	load_texture(t_data *data, int index, char *path)
{
	data->textures[index] = xpm_to_img(data, path);
	if (!data->textures[index])
		clean_exit(data, err_msg(path, ERR_TEX_INVALID, FAILURE));
}

void	init_textures(t_data *data)
{
	int		i;
	char	*texture_paths[] = {
		data->texinfo.north,
		data->texinfo.south,
		data->texinfo.east,
		data->texinfo.west,
		"./textures/bonus/door.xpm",
		"./textures/bonus/skull.xpm",
		"./textures/bonus/library1.xpm",
		"./textures/bonus/library2.xpm",
		"./textures/bonus/secret.xpm",
		"./textures/bonus/wbase.xpm",
		"./textures/bonus/wpaint1.xpm",
		"./textures/bonus/wpaint2.xpm",
		"./textures/bonus/wpaint3.xpm",
		"./textures/bonus/wred.xpm"
	};
	int		texture_count = sizeof(texture_paths) / sizeof(texture_paths[0]);
	data->textures = ft_calloc(texture_count, sizeof *data->textures);
	if (!data->textures)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, FAILURE));

	i = 0;
	while (i < texture_count)
	{
		load_texture(data, i, texture_paths[i]);
		i++;
	}
}

void	init_title_screen(t_data *data)
{
	data->title_img = mlx_xpm_file_to_image(
		data->mlx,
		"./textures/title_screen.xpm",
		&data->win_width,
		&data->win_height);
	if (!data->title_img)
		clean_exit(data, err_msg("./textures/title_screen.xpm",
			ERR_TEX_INVALID, FAILURE));
}

void	init_texinfo(t_texinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->size = TEX_SIZE;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->x = 0;
	textures->y = 0;
}
