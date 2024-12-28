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

static long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static char	*generate_frame_filename(int frame_index)
{
	char	*filename;

	filename = malloc(50);
	if (!filename)
		return (NULL);
	sprintf(filename, "./textures/intro/frame_%04d.xpm", frame_index + 1);
	return (filename);
}

static void	show_img(t_data *data, char *file, long *last_time, long curr_time)
{
	void	*img;
	int		width;
	int		height;

	width = data->win_width;
	height = data->win_height;
	img = mlx_xpm_file_to_image(data->mlx, file, &width, &height);
	free(file);
	if (!img)
	{
		printf(RED "Erreur : Impossible de charger la frame\n" RESET);
		return ;
	}
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
	*last_time = curr_time;
}

void	play_intro_video(t_data *data)
{
	int		frame_index;
	long	last_frame_time;
	long	current_time;
	char	*filename;

	frame_index = 0;
	last_frame_time = 0;
	while (frame_index < 324)
	{
		listen_for_input(data);
		current_time = get_time_in_ms();
		if (current_time - last_frame_time >= (1000 / 30))
		{
			filename = generate_frame_filename(frame_index);
			if (!filename)
				return ;
			show_img(data, filename, &last_frame_time, current_time);
			frame_index++;
		}
		data->start_game = 3;
	}
}
