/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 22:10:36 by yonieva           #+#    #+#             */
/*   Updated: 2024/02/13 18:44:06 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *blocmem,	size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		((unsigned char *)blocmem)[i] = 0;
		i++;
	}
}
