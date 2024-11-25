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

void	print_controls(void)
{
	printf(RED"\n");
	printf("                                           ,--,  ,.-.         \n");
    printf("              ,                   \\,       '-,-`,'-.' | ._    \n");
    printf("             /|           \\    ,   |\\         }  )/  / `-,',  \n");
    printf("             [ ,          |\\  /|   | |        /  \\|  |/`  ,`  \n");
    printf("             | |       ,.`  `,` `, | |  _,...(   (      .',   \n");
    printf("             \\  \\  __ ,-` `  ,  , `/ |,'      Y     (   /_L\\  \n");
    printf("              \\  \\_\\,``,   ` , ,  /  |         )         _,/  \n");
    printf("               \\  '  `  ,_ _`_,-,<._.<        /         /     \n");
    printf("               ', `>.,`  `  `   ,., |_      |         /       \n");
    printf("                 \\/`  `,   `   ,`  | /__,.-`    _,   `\\       \n");
    printf("             -,-..\\  _  \\  `  /  ,  / `._) _,-\\`       \\      \n");
    printf("              \\_,,.) /\\    ` /  / ) (-,, ``    ,        |     \n");
    printf("             ,` )  | \\_\\       '-`  |  `(               \\     \n");
    printf("            /  /```(   , --, ,' \\   |`<`    ,            |    \n");
    printf("           /  /_,--`\\   <\\  V /> ,` )<_/)  | \\      _____)    \n");
    printf("     ,-, ,`   `   (_,\\ \\    |   /) / __/  /   `----`          \n");
    printf("    (-, \\           ) \\ ('_.-._)/ /,`    /                    \n");      
    printf("     | /  `          `/ \\ V   V, /`     /                     \n");
	printf("(   ,``-     \\/|         \\-A.A-`|     /     CASTLEVANIA 3d   \n");
	printf(" ,>,_ )_,..(    )\\          -,,_-`  _--`    By Esteve Gauthier & Onieva Yoan\n");
	printf("(_ \\|`   _,/_  /  \\_            ,--`                          \n");
	printf("\\( `   <.,../`     `-.._   _,-                                \n\n");
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