/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:27:36 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/14 22:27:36 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

static void	free_texinfo(t_texinfo *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

static void	free_map(t_data *data)
{
	if (data->mapinfo.fd > 0)
		close(data->mapinfo.fd);
	if (data->mapinfo.file)
		free_tab((void **)data->mapinfo.file);
	if (data->map)
		free_tab((void **)data->map);
}

int	free_data(t_data *data)
{
	if (data->textures)
	{
		free_tab((void **)data->textures);
		data->textures = NULL;
	}
	if (data->texture_pixels)
	{
		free_tab((void **)data->texture_pixels);
		data->texture_pixels = NULL;
	}
	free_texinfo(&data->texinfo);
	free_map(data);
	return (FAILURE);
}
