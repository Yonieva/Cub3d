/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:20:00 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/25 14:20:00 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*int x : Indice de la colonne de l'écran actuellement traitée 
(entre 0 et la largeur de la fenêtre, WIN_WIDTH - 1).
t_ray *ray : Pointeur vers une structure ray contenant les informations 
relatives au rayon (direction, position, distances, etc.).
t_player *player : Pointeur vers la struct player qui contient :
Position (pos_x, pos_y) : Position actuelle du joueur sur la carte.
Direction (dir_x, dir_y) : Direction dans laquelle le joueur regarde.
Plan caméra (plane_x, plane_y) : Décrit le champ de vision (FOV) du joueur.*/
static void	init_raycasting_info(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
/*camera_x détermine la position relative du rayon par rapport à la caméra :
-1 : Rayon le plus à gauche de l'écran.
0 : Rayon au centre de l'écran.
1 : Rayon le plus à droite de l'écran.
Cette valeur est calculée en fonction de x, la colonne actuelle, et de la largeur totale de l'écran WIN_WIDTH.
Cela permet de mapper chaque colonne de pixels de l'écran à un rayon unique dans le champ de vision*/
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
/*Calcul de la direction du rayon*/
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
/*map_x et map_y : Indiquent la case actuelle de la carte dans laquelle le joueur se trouve.
La position du joueur, initialement en flottant (par exemple, 5.23), est convertie en un entier pour identifier la case correspondante.*/
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
/*Décrivent la distance que le rayon doit parcourir pour traverser une ligne de grille (soit en X, soit en Y).
Elles sont calculées comme l'inverse de la direction du rayon :
Plus la direction est verticale (grande valeur de dir_y), plus deltadist_x sera grande.
Plus la direction est horizontale (grande valeur de dir_x), plus deltadist_y sera grande.
L'utilisation de fabs garantit que les distances sont toujours positives.*/
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

/*initialise les paramètres nécessaires pour exécuter l'algorithme DDA*/
/*Cet algor trace un rayon à travers la map, pour savoir où il rencontre un mur.*/
/*Si le rayon est dirigé vers la gauche (dir_x < 0), step_x est défini à -1 pour indiquer un mouvement dans la direction négative.
Sinon (dir_x >= 0), step_x est défini à 1 pour un mouvement vers la droite.(idem pour haut bas avec y) */
/*Si le rayon va vers la gauche, Distance entre la position actuelle du joueur et le bord gauche de la case où il se trouve.
Multiplier cette distance par deltadist_x (distance pour traverser une case en X).*/
static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

/*À chaque itération de la boucle, l'algorithme compare les distances sidedist_x et sidedist_y pour déterminer dans quelle direction le rayon doit avancer :
Si sidedist_x < sidedist_y : Le rayon va avancer horizontalement (sur l'axe X).
ray->sidedist_x += ray->deltadist_x; : On ajoute l'incrément de distance en X.
ray->map_x += ray->step_x; : On déplace la position du rayon dans la direction horizontale (gauche ou droite).
ray->side = 0; : On marque que l'on a touché un côté horizontal de la grille.
Sinon (sidedist_y <= sidedist_x) : Le rayon va avancer verticalement (sur l'axe Y).
ray->sidedist_y += ray->deltadist_y; : On ajoute l'incrément de distance en Y.
ray->map_y += ray->step_y; : On déplace la position du rayon dans la direction verticale (haut ou bas).
ray->side = 1; : On marque que l'on a touché un côté vertical de la grille.
Note : La direction dans laquelle avancer est déterminée en fonction de quelle distance (X ou Y) 
est la plus petite, car cela correspond au prochain bord de cellule que le rayon va traverser.*/
static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > data->mapinfo.height - 0.25
			|| ray->map_x > data->mapinfo.width - 1.25)
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

/*Calculer la distance entre la position du joueur et le mur frappé par le rayon (wall_dist).
Déterminer la hauteur de la ligne projetée à l'écran (line_height) en fonction de cette distance, en respectant les principes de perspective.
Trouver les limites de cette ligne (draw_start et draw_end) afin de savoir où dessiner sur l'écran.
Calculer la position du point d'impact sur le mur (wall_x) pour appliquer correctement une texture.*/
static void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

/*effectue un balayage horizontal de l'écran (colonne par colonne de pixels) 
pour déterminer quelle partie de l'environnement 
est visible du point de vue du joueur.*/
int	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x < data->win_width)
	{
		init_raycasting_info(x, &ray, player);
		set_dda(&ray, player);
		perform_dda(data, &ray);
		calculate_line_height(&ray, data, player);
		update_texture_pixels(data, &data->texinfo, &ray, x);
		x++;
	}
	return (SUCCESS);
}