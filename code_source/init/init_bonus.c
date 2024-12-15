/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:08:47 by gaesteve          #+#    #+#             */
/*   Updated: 2024/12/15 21:17:00 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_door(t_data *data)
{
	int y = 0;
	int x;

	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D')
			{
				data->door.pos_x = x;
				data->door.pos_y = y;
				data->door.is_open = 0; // La porte est fermée par défaut
				printf("Door found at (%d, %d)\n", x, y);
				return;
			}
			x++;
		}
		y++;
	}
	data->door.pos_x = -1; // Aucune porte trouvée
	data->door.pos_y = -1;
}
