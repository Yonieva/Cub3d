/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:11:04 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/20 15:11:04 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_elements(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	data->player.dir = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (map_tab[i][j] >= 9 && map_tab[i][j] <= 13)
				j++;
			if (!BONUS && !(ft_strchr("10NSEW", map_tab[i][j])))
				return (err_msg(data->mapinfo.path, ERR_INV_LETTER, FAILURE));
			if (BONUS && !(ft_strchr("10NSEWDCKLVBHOTRI", map_tab[i][j])))
				return (err_msg(data->mapinfo.path, ERR_INV_LETTER, FAILURE));
			if (ft_strchr("NSEW", map_tab[i][j]) && data->player.dir != '0')
				return (err_msg(data->mapinfo.path, ERR_NUM_PLAYER, FAILURE));
			if (ft_strchr("NSEW", map_tab[i][j]) && data->player.dir == '0')
				data->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/*verif lign + et -, si+ courte que la colone du joueur = dehors de map*/
/*Si l'une de ces cases autour du j est un espace, zone invalide*/
static int	check_position_is_valid(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	i = (int)data->player.pos_y;
	j = (int)data->player.pos_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| is_a_white_space(map_tab[i][j - 1]) == SUCCESS
		|| is_a_white_space(map_tab[i][j + 1]) == SUCCESS
		|| is_a_white_space(map_tab[i - 1][j]) == SUCCESS
		|| is_a_white_space(map_tab[i + 1][j]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

/*stock position exacte du p1 + le met au centre de la case + met a 0 (vide)*/
static int	check_player_position(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	if (data->player.dir == '0')
		return (err_msg(data->mapinfo.path, ERR_PLAYER_DIR, FAILURE));
	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSEW", map_tab[i][j]))
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(data, map_tab) == FAILURE)
		return (err_msg(data->mapinfo.path, ERR_PLAYER_POS, FAILURE));
	return (SUCCESS);
}

/*check si plus aucun char apres la map*/
static int	check_map_is_at_the_end(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/*check si au moins 3 ligne sur la map*/
int	check_map_validity(t_data *data, char **map_tab)
{
	if (!data->map)
		return (err_msg(data->mapinfo.path, ERR_MAP_MISSING, FAILURE));
	if (check_map_sides(&data->mapinfo, map_tab) == FAILURE)
		return (err_msg(data->mapinfo.path, ERR_MAP_NO_WALLS, FAILURE));
	if (data->mapinfo.height < 3)
		return (err_msg(data->mapinfo.path, ERR_MAP_TOO_SMALL, FAILURE));
	if (check_map_elements(data, map_tab) == FAILURE)
		return (FAILURE);
	if (check_player_position(data, map_tab) == FAILURE)
		return (FAILURE);
	if (check_map_is_at_the_end(&data->mapinfo) == FAILURE)
		return (err_msg(data->mapinfo.path, ERR_MAP_LAST, FAILURE));
	return (SUCCESS);
}
