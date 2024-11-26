/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:51:01 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/26 14:51:01 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static long	get_time_in_ms()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static char	*generate_frame_filename(int frame_index)
{
	char *filename;
	filename = malloc(50); // Allouer assez d'espace pour le chemin
	if (!filename)
		return (NULL);
	sprintf(filename, "./textures/intro/frame_%04d.xpm", frame_index + 1);
	return (filename);
}

void	play_intro_video(t_data *data)
{
	int frame_index = 0;
	long last_frame_time = 0;
	long current_time;

	// Boucle d'affichage des frames
	while (frame_index < 324) // Nombre total de frames
	{
		listen_for_input(data);
		current_time = get_time_in_ms();
		if (current_time - last_frame_time >= (1000 / 30)) // 30 FPS
		{
			char *filename = generate_frame_filename(frame_index);

			// Charger la frame
			void *frame_img = mlx_xpm_file_to_image(
				data->mlx, filename, &data->win_width, &data->win_height);
			free(filename);

			if (!frame_img)
			{
				printf(RED "Erreur : Impossible de charger la frame %d\n" RESET, frame_index);
				return;
			}

			// Afficher la frame dans la fenêtre
			mlx_put_image_to_window(data->mlx, data->win, frame_img, 0, 0);

			// Libérer l'image une fois affichée
			mlx_destroy_image(data->mlx, frame_img);

			// Passer à la frame suivante
			frame_index++;
			last_frame_time = current_time;
		}
		data->start_game = 3;
	}
}