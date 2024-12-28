/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:01:37 by gaesteve          #+#    #+#             */
/*   Updated: 2024/12/28 20:02:29 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
