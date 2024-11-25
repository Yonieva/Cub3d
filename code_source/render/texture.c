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

/*Si le mur frappé est horizontal (ray->side == 0) :
Si le rayon se dirige vers la gauche (ray->dir_x < 0), la texture de l'OUEST (WEST) est utilisée.
Si le rayon se dirige vers la droite (ray->dir_x >= 0), la texture de l'EST (EAST) est utilisée.

Si le mur frappé est vertical (ray->side == 1) :
Si le rayon se dirige vers le bas (ray->dir_y > 0), la texture du SUD (SOUTH) est utilisée.
Si le rayon se dirige vers le haut (ray->dir_y <= 0), la texture du NORD (NORTH) est utilisée*/
static void	get_texture_index(t_data *data, t_ray *ray)
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

/*Cette fonction applique la texture sélectionnée sur une colonne de l'écran 
en calculant quel pixel de la texture correspond à chaque ligne de pixels entre draw_start et draw_end.
t_data *data : Données du jeu, incluant la liste des textures et des pixels à afficher.
t_texinfo *tex : Contient les informations sur la texture (dimensions, index, position actuelle).
t_ray *ray : Contient les informations sur le rayon (hauteur de ligne, position sur le mur).
int x : Position horizontale actuelle sur l'écran.*/
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
	data->texture_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->texture_pixels);
	if (!data->texture_pixels)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->texture_pixels);
		if (!data->texture_pixels[i])
			clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
		i++;
	}
}