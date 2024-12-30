/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:12:33 by gaesteve          #+#    #+#             */
/*   Updated: 2024/12/30 21:50:29 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Calcul de la distance entre le joueur et la porte*/
/*Si le joueur est proche et la porte est fermée*/
/*Si le joueur s'éloigne et la porte est ouverte*/
void	check_door(t_data *data)
{
	double	dist_x;
	double	dist_y;
	double	distance;

	if (data->door.pos_x == -1 || data->door.pos_y == -1)
		return ;
	dist_x = data->player.pos_x - data->door.pos_x;
	dist_y = data->player.pos_y - data->door.pos_y;
	distance = sqrt(dist_x * dist_x + dist_y * dist_y);
	if (distance < 1.5 && !data->door.is_open)
	{
		data->door.is_open = 1;
		data->map[data->door.pos_y][data->door.pos_x] = '0';
		printf("Door opened at (%d, %d)\n", data->door.pos_x, data->door.pos_y);
	}
	else if (distance >= 1.5 && data->door.is_open)
	{
		data->door.is_open = 0;
		data->map[data->door.pos_y][data->door.pos_x] = 'D';
		printf("Door closed at (%d, %d)\n", data->door.pos_x, data->door.pos_y);
	}
}
