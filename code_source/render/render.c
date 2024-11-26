/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:07:06 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/25 14:07:06 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*permet de définir la couleur d'un pixel à une position (x, y) dans une image (représentée par la structure t_img), 
en utilisant un tableau de pixels.*/
void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;
	/*chaque pixel est représenté par 4 octets (pour le format RGBA*/
	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

/*Cette fonction est responsable de la détermination du pixel à afficher sur l'écran pour une position donnée (x, y). 
Elle choisit entre les différentes textures, couleurs de plafond ou de sol, ou encore de l'espace vide, 
en fonction des données de texture et de l'élévation (position y) du pixel*/
static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

/*La fonction render_frame est responsable de la création de l'image complète à afficher à l'écran. 
Elle parcourt tous les pixels de l'image et utilise set_frame_image_pixel pour remplir chaque pixel
avec les bonnes données (textures, couleurs de plafond ou de sol).*/
static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

static void	render_raycast(t_data *data)
{
	init_texture_pixels(data);
	init_ray(&data->ray);
	raycasting(&data->player, data);
	render_frame(data);
}

void	render_images(t_data *data)
{
	if(!data->start_game)
		draw_title_screen(data);
	else if(data->start_game == 1)
		play_intro_video(data);
	else
	{
		render_raycast(data);
		if (BONUS)
			render_minimap(data);
	}
}

int	render(t_data *data)
{
	data->player.has_moved += move_player(data);
	if (data->player.has_moved == 0)
		return (0);
	render_images(data);
	return (0);
}