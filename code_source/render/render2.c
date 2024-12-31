/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:08:36 by gaesteve          #+#    #+#             */
/*   Updated: 2024/12/31 18:10:10 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*permet de définir la couleur d'un pixel à une position (x, y) dans une image
(représentée par la structure t_img), en utilisant un tableau de pixels.*/
void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

/*Cette fonction est responsable de la détermination du pixel à afficher sur
l'écran pour une position donnée (x, y). Elle choisit entre les différentes
textures, couleurs de plafond ou de sol, ou encore de l'espace vide, en
fonction des données de texture et de l'élévation (position y) du pixel*/
void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}
