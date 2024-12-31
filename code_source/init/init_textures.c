/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:34:03 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/31 19:32:40 by gaesteve         ###   ########.fr       */
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

	init_texture_img(data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * data->texinfo.size * data->texinfo.size);
	if (!buffer)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	y = 0;
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
	if (path)
	{
		data->textures[index] = xpm_to_img(data, path);
		if (!data->textures[index])
			clean_exit(data, err_msg(path, ERR_TEX_INVALID, FAILURE));
	}
	else
		data->textures[index] = NULL;
}

static void	init_xpm(char **texture_paths, t_texinfo *texinfo)
{
	texture_paths[0] = texinfo->north;
	texture_paths[1] = texinfo->south;
	texture_paths[2] = texinfo->east;
	texture_paths[3] = texinfo->west;
	if (BONUS)
	{
		texture_paths[4] = "./textures/bonus/door.xpm";
		texture_paths[5] = "./textures/bonus/skull.xpm";
		texture_paths[6] = "./textures/bonus/library1.xpm";
		texture_paths[7] = "./textures/bonus/library2.xpm";
		texture_paths[8] = "./textures/bonus/secret.xpm";
		texture_paths[9] = "./textures/bonus/wbase.xpm";
		texture_paths[10] = "./textures/bonus/wpaint1.xpm";
		texture_paths[11] = "./textures/bonus/wpaint2.xpm";
		texture_paths[12] = "./textures/bonus/wpaint3.xpm";
		texture_paths[13] = "./textures/bonus/wred.xpm";
		texture_paths[14] = "./textures/bonus/head.xpm";
	}
}

void	textures_data(t_data *data)
{
	int		texture_count;
	char	*texture_paths[15];

	texture_count = get_texture_count();
	init_xpm(texture_paths, &data->texinfo);
	data->textures = ft_calloc(texture_count + 1, sizeof(*data->textures));
	if (!data->textures)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, FAILURE));
	init_textures(data, texture_paths, texture_count);
}

void	init_textures(t_data *data, char **texture_paths, int texture_count)
{
	int	i;

	i = 0;
	while (i < texture_count)
	{
		load_texture(data, i, texture_paths[i]);
		i++;
	}
}
