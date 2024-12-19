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
	// Vérification des textures principales (N, S, E, W)
	if (!textures->north || !textures->south || !textures->west || !textures->east)
		return (err_msg(data->mapinfo.path, ERR_TEX_MISSING, FAILURE));

	// Mode BONUS : Vérification des textures sol et plafond
	if (BONUS)
	{
		if (!textures->floor_texture || !textures->ceiling_texture)
			return (err_msg(data->mapinfo.path, ERR_TEX_MISSING, FAILURE));
		// Vérifie que les fichiers de textures existent
		if (check_file(textures->floor_texture, false) == FAILURE ||
			check_file(textures->ceiling_texture, false) == FAILURE)
			return (err_msg(data->mapinfo.path, ERR_TEX_INVALID, FAILURE));
	}
	// Mode standard : Vérification des couleurs RGB pour le sol/plafond
	else
	{
		if (!textures->floor || !textures->ceiling)
			return (err_msg(data->mapinfo.path, ERR_COLOR_MISSING, FAILURE));
		if (check_valid_rgb(textures->floor) == FAILURE ||
			check_valid_rgb(textures->ceiling) == FAILURE)
			return (err_msg(data->mapinfo.path, ERR_TEX_INVALID, FAILURE));
		// Convertit les couleurs RGB en hexadécimal
		textures->hex_floor = convert_rgb_to_hex(textures->floor);
		textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	}
	return (SUCCESS);
}



