/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:41:44 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/25 15:41:44 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*XK_Left fait partie de la norme X11 keysym*/
static int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_Left)
		data->player.rotate -= 1;
	if (key == XK_Right)
		data->player.rotate += 1;
	if (key == XK_w && data->start_game == 0)
		data->start_game = 1;
	if (key == XK_w)
		data->player.move_y = 1;
	if (key == XK_a)
		data->player.move_x = -1;
	if (key == XK_s)
		data->player.move_y = -1;
	if (key == XK_d)
		data->player.move_x = 1;
	return (0);
}

/*Si l'utilisateur relâche la touche W (indiquée par XK_w) et que le joueur 
était en mouvement vers l'avant  on arrête ce mouvement 
en remplaçant move_y par 0*/
static int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_w && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == XK_s && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == XK_a && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == XK_d && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == XK_Left && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (key == XK_Right && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);
}

/*La fonction wrap_mouse_position permet de capturer la position de la souris 
lorsqu'elle approche des bords de la fenêtre du jeu et de la déplacer instantanément 
à l'autre bord, créant ainsi un effet de "bouclage" horizontal de la souris.
 Cela permet d'éviter que la souris sorte de la fenêtre du jeu.

Effet de "wrap" : Lorsque la souris touche un bord (gauche ou droit), elle 
se déplace instantanément vers l'autre bord de l'écran.
Distance de "wrap" : La fonction utilise DIST_EDGE_MOUSE_WRAP pour 
définir la distance au bord avant de déplacer la souris*/
static void	wrap_mouse_position(t_data *data, int x, int y)
{
	if (x > data->win_width - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = data->win_width - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
}

/*gestionnaire d'événements pour les mouvements de la souris. 
Elle est appelée lorsqu'un mouvement de la souris est détecté dans la fenêtre. 
permet de contrôler la rotation du joueur en fonction du déplacement horizontal 
de la souris (gauche ou droite) et de maintenir un effet de "wrap" pour que 
la souris ne quitte pas la fenêtre.*/
static int	mouse_motion_handler(int x, int y, t_data *data)
{
	static int	old_x = WIN_WIDTH / 2;

	wrap_mouse_position(data, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		data->player.has_moved += rotate_player(data, -1);
	else if (x > old_x)
		data->player.has_moved += rotate_player(data, 1);
	old_x = x;
	return (0);
}

void	listen_for_input(t_data *data)
{
	/*fermeture de la fenetre*/
	mlx_hook(data->win, ClientMessage, NoEventMask, quit_cub3d, data);
	/*enregistre un gestionnaire pour l'événement KeyPress*/
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
	/*enregistre un gestionnaire pour l'événement KeyRelease*/
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_handler, data);
	/*écoute des mouvements de la souris*/
	if (BONUS)
		mlx_hook(data->win, MotionNotify, PointerMotionMask,
			mouse_motion_handler, data);
}