/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:41:42 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/18 15:13:40 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t nb)
{
	size_t	i;

	i = 0;
	if (nb == 0)
	{
		return (0);
	}
	while (i < nb && str1[i] && str2[i] && str1[i] == str2[i])
	{
		i++;
	}
	if (i < nb)
	{
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}
