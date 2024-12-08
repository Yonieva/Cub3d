/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:18:46 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/14 22:18:46 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_title_screen(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->title_img, 0, 0);
}

void	print_controls(void)
{
	printf("░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(YELLOW "\tW" RESET ": move forward\t");
	printf(YELLOW "\tS" RESET ": move backward\n");
	printf(YELLOW "\tA" RESET ": strafe left\t");
	printf(YELLOW "\tD" RESET ": strafe right\n");
	printf(YELLOW "\t<" RESET ": rotate left\t");
	printf(YELLOW "\t>" RESET ": rotate right\n");
	if (BONUS)
		printf(YELLOW "\tMouse" RESET ": rotate view\n");
	printf("\n");
}

