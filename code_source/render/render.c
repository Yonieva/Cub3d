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
	/*chaque pixel est représenté par 4 octets (pour le format RGBA)*/
	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

/*Cette fonction est responsable de la détermination du pixel à afficher sur l'écran pour une position donnée (x, y).
Elle choisit entre les différentes textures, couleurs de plafond ou de sol, ou encore de l'espace vide,
en fonction des données de texture et de l'élévation (position y) du pixel*/
// static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
// {
// 	if (data->texture_pixels[y][x] > 0)
// 		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
// 	else if (y < data->win_height / 2)
// 		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
// 	else if (y < data->win_height -1)
// 		set_image_pixel(image, x, y, data->texinfo.hex_floor);
// }

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	// Vérifie si le pixel actuel correspond à un mur
	if (data->texture_pixels[y][x] > 0)
	{
		// Utilise la couleur du mur
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	}
	// Si le pixel est au-dessus de la moitié de la fenêtre (plafond)
	else if (y < data->win_height / 2)
	{
		// Si BONUS est activé et qu'une texture de plafond est définie
		if (BONUS && data->texinfo.ceiling_texture)
		{
			// Calcule les coordonnées de la texture et applique-la
			int tex_x = x % TEX_SIZE;
			int tex_y = y % TEX_SIZE;
			int color = data->textures[CEILING_TEXTURE_INDEX][tex_y * TEX_SIZE + tex_x];
			set_image_pixel(image, x, y, color);
		}
		else
		{
			// Sinon, applique la couleur unie du plafond
			set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
		}
	}
	// Si le pixel est en-dessous de la moitié de la fenêtre (sol)
	else
	{
		// Si BONUS est activé et qu'une texture de sol est définie
		if (BONUS && data->texinfo.floor_texture)
		{
			// Calcule les coordonnées de la texture et applique-la
			int tex_x = x % TEX_SIZE;
			int tex_y = y % TEX_SIZE;
			int color = data->textures[FLOOR_TEXTURE_INDEX][tex_y * TEX_SIZE + tex_x];
			set_image_pixel(image, x, y, color);
		}
		else
		{
			// Sinon, applique la couleur unie du sol
			set_image_pixel(image, x, y, data->texinfo.hex_floor);
		}
	}
}

static void	render_floor_and_ceiling(t_data *data, t_img *image)
{
	int x, y;
	double ray_dir_x0, ray_dir_y0, ray_dir_x1, ray_dir_y1;
	double row_distance, floor_step_x, floor_step_y;
	double floor_x, floor_y;

	// Position et direction du joueur
	double pos_x = data->player.pos_x;
	double pos_y = data->player.pos_y;

	ray_dir_x0 = data->player.dir_x - data->player.plane_x;
	ray_dir_y0 = data->player.dir_y - data->player.plane_y;
	ray_dir_x1 = data->player.dir_x + data->player.plane_x;
	ray_dir_y1 = data->player.dir_y + data->player.plane_y;

	// Parcourir chaque ligne de pixels sous l'horizon
	for (y = data->win_height / 2; y < data->win_height; y++)
	{
		// Distance de la caméra au plan du sol
		row_distance = (0.5 * data->win_height) / (y - data->win_height / 2);

		// Direction du rayon pour chaque colonne
		floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / data->win_width;
		floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / data->win_width;

		// Coordonnées du sol initialisées
		floor_x = pos_x + row_distance * ray_dir_x0;
		floor_y = pos_y + row_distance * ray_dir_y0;

		for (x = 0; x < data->win_width; x++)
		{
			int floor_tex_x, floor_tex_y;
			int ceiling_tex_x, ceiling_tex_y;

			// Calculer les coordonnées dans la texture
			floor_tex_x = (int)(floor_x * TEX_SIZE) % TEX_SIZE;
			floor_tex_y = (int)(floor_y * TEX_SIZE) % TEX_SIZE;
			ceiling_tex_x = floor_tex_x; // Même calcul pour le plafond
			ceiling_tex_y = floor_tex_y;

			// Couleurs pour le sol et le plafond
			int floor_color = data->textures[TFLOOR][TEX_SIZE * floor_tex_y + floor_tex_x];
			int ceiling_color = data->textures[TCEILING][TEX_SIZE * ceiling_tex_y + ceiling_tex_x];

			// Appliquer les pixels à l'image
			set_image_pixel(image, x, y, floor_color);
			set_image_pixel(image, x, data->win_height - y - 1, ceiling_color);

			// Incrémenter les coordonnées du sol
			floor_x += floor_step_x;
			floor_y += floor_step_y;
		}
	}
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
	render_floor_and_ceiling(data, &image);
	init_texture_pixels(data); // essayer d enlever ca apres
	raycasting(&data->player, data);

	// Dessiner les pixels dans l'image
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
	// Afficher l'image finale
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
	else if(data->start_game == 1 && BONUS)
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
	if (BONUS)
		check_door(data);
	render_images(data);
	return (0);
}
