/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:29:05 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/21 21:29:05 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int	i;

	if (BONUS)
		return (SUCCESS);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (err_msg_val(rgb[i], ERR_TEX_RGB_VAL, FAILURE));
		i++;
	}
	return (SUCCESS);
}

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	check_textures_validity(t_data *data, t_texinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west || !textures->east)
		return err_msg(data->mapinfo.path, ERR_TEX_MISSING, FAILURE);

	if (BONUS)
	{
		if (!textures->floor_texture || !textures->ceiling_texture)
			return err_msg(data->mapinfo.path, ERR_TEX_MISSING, FAILURE);
	}
	else
	{
		if (!textures->floor || !textures->ceiling)
			return err_msg(data->mapinfo.path, ERR_COLOR_MISSING, FAILURE);

		if (check_valid_rgb(textures->floor) == FAILURE || check_valid_rgb(textures->ceiling) == FAILURE)
			return FAILURE;

		textures->hex_floor = convert_rgb_to_hex(textures->floor);
		textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	}

	if (check_file(textures->north, false) == FAILURE
		|| check_file(textures->south, false) == FAILURE
		|| check_file(textures->west, false) == FAILURE
		|| check_file(textures->east, false) == FAILURE)
		return FAILURE;

	if (BONUS)
	{
		if (check_file(textures->floor_texture, false) == FAILURE
			|| check_file(textures->ceiling_texture, false) == FAILURE)
			return FAILURE;
	}

	return SUCCESS;
}




