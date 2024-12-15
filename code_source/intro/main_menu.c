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

static void	print_terminal(void)
{
    printf("                          ,--.\n");
    printf("                         K,   }\n");
    printf("                        /  `Y`\n");
    printf("                   _   /   /\n");
    printf("                  {_'-K.__/\n");
    printf("                   `/-.__L._\n");
    printf("                    /  ' /`\\_}\n");
    printf("                   /  ' /     -CASTLEVANIA 3D-\n");
    printf("     ,-'~~~~    ~~/  ' /_\n");
    printf("   ,'             ``~~~%%',\n");
    printf("  (                        Y\n");
    printf(" {                      %% I\n");
    printf("{      -                    `.\n");
    printf("|       ',                %% )\n");
    printf("|        |   ,..__      __. Y\n");
    printf("|    .,_./  Y ' / ^Y   J   )|\n");
    printf("\\           |' /   |   |   ||\n");
    printf(" \\          L_/    . _ (_,.'(\n");
    printf("  \\,   ,      ^^\"\"' / |      )\n");
    printf("    \\_  \\          /,L]     /\n");
    printf("      '-_`-,       ` `   ./`\n");
    printf("         `-(_            )\n");
    printf("             ^^\\..___,.--`\n");
}

void	print_controls(void)
{
	print_terminal();
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

