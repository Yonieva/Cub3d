/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:07:19 by yonieva           #+#    #+#             */
/*   Updated: 2024/10/13 16:07:19 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (printf(RED "\terror nb args: ./cub3d maps/xx.cub \n"RESET));
	init_data(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	if (BONUS)
		init_door(&data);
	init_mlx(&data);
	init_textures(&data);
	print_controls();
	render_images(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
