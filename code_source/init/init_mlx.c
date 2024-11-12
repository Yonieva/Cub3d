/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:09:25 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/07 14:09:25 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*initialise une nouvelle image avec une largeur et une hauteur*/
void	init_img(t_data *data, t_img *image, int width, int height)
{
	/*Nettoie les données de l'image*/
	init_img_clean(image);
	image->img = mlx_new_image(data->mlx, width, height);
	if (image->img == NULL)
		clean_exit(data, err_msg("mlx", ERR_MLX_IMG, 1));
	/*Obtient l'adress des pixels de l'img, pour les manipuler.*/
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

/*initialise une image à partir d'un fichier de texture*/
void	init_texture_img(t_data *data, t_img *image, char *path)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size,
			&data->texinfo.size);
	if (image->img == NULL)
		clean_exit(data, err_msg("mlx", ERR_MLX_IMG, 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void	init_mlx(t_data *data)
{
	/*Initialise la mlx*/ 
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_exit(data, err_msg("mlx", ERR_MLX_START, 1));
	/*Creaton de la fenetre*/ 
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Castlevania 3d");
	if (!data->win)
		clean_exit(data, err_msg("mlx", ERR_MLX_WIN, 1));
	if (BONUS)
		mlx_mouse_move(data->mlx, data->win, data->win_width / 2,
			data->win_height / 2);
	return ;
}