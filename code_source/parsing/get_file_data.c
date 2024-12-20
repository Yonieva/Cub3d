/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:12:05 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/19 16:12:05 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*extrait le chemin d une texture à partir de la position j.*/
char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

/*associe les textures(north, south, west, east) aux chemins extraits*/
static int	fill_direction_textures(t_texinfo *textures, char *line, int j)
{
	// Gestion des directions standard (NO, SO, etc.)
	if (line[j] == 'N' && line[j + 1] == 'O' && !(textures->north))
		textures->north = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(textures->south))
		textures->south = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(textures->west))
		textures->west = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(textures->east))
		textures->east = get_texture_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

/*Analyser une ligne (map[i]) et detecte texture couleur,direction et map*/
static int	ignore_whitespaces_get_info(t_data *data, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1]))
		{
			if (fill_direction_textures(&data->texinfo, map[i], j) == ERR)
				return (err_msg(data->mapinfo.path, ERR_TEX_INVALID, FAILURE));
			return (BREAK);
		}
		else if (fill_color(data, &data->texinfo, map[i], j) == FAILURE)
			return (err_msg(data->mapinfo.path, ERR_TEX_INVALID, FAILURE));
		return (BREAK);
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (create_map(data, map, i) == FAILURE)
			return (err_msg(data->mapinfo.path, ERR_INVALID_MAP, FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}

/*lis fichier pour analyser et extraire (textures, couleurs, map)*/
int	get_file_data(t_data *data, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = ignore_whitespaces_get_info(data, map, i, j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
