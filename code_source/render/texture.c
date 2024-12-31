/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:08:42 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/25 14:08:42 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_texture_index(t_data *data, char cell)
{
	if (cell == 'D')
		data->texinfo.index = DOOR;
	else if (cell == 'C')
		data->texinfo.index = SKULL;
	else if (cell == 'K')
		data->texinfo.index = LIB1;
	else if (cell == 'L')
		data->texinfo.index = LIB2;
	else if (cell == 'V')
		data->texinfo.index = SECRET;
	else if (cell == 'B')
		data->texinfo.index = WBASE;
	else if (cell == 'H')
		data->texinfo.index = WPAINT1;
	else if (cell == 'O')
		data->texinfo.index = WPAINT2;
	else if (cell == 'T')
		data->texinfo.index = WPAINT3;
	else if (cell == 'R')
		data->texinfo.index = WRED;
	else if (cell == 'I')
		data->texinfo.index = HEAD;
}

static void	assign_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texinfo.index = WEST;
		else
			data->texinfo.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texinfo.index = SOUTH;
		else
			data->texinfo.index = NORTH;
	}
}

static void	get_texture_index(t_data *data, t_ray *ray)
{
	char	cell;

	cell = data->map[ray->map_y][ray->map_x];
	assign_texture_index(data, cell);
	if (cell == '1')
		assign_wall_texture(data, ray);
}

/*Cette fonction applique la texture sélectionnée sur une colonne de l'écran
en calculant quel pixel de la texture correspond à chaque ligne de pixels
entre draw_start et draw_end.*/
void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_texture_index(data, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->texture_pixels[y][x] = color;
		y++;
	}
}

/*initialise un tableau 2d
pour stocker les infos des pixels des textures
pour reagir au changement de dimensions de la fenetre*/
void	init_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		free_tab((void **)data->texture_pixels);
	data->texture_pixels = ft_calloc(data->win_height + 1, sizeof(int *));
	if (!data->texture_pixels)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1, sizeof(int));
		if (!data->texture_pixels[i])
			clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
		i++;
	}
	data->texture_pixels[i] = NULL;
}
