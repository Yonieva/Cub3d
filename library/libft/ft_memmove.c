/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:06:44 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/17 18:24:01 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t		i;
	char		*bloc1;
	char		*bloc2;

	bloc1 = (char *)dest;
	bloc2 = (char *)src;
	if (!bloc1 && !bloc2)
		return (NULL);
	if (bloc2 < bloc1)
	{
		while (len > 0)
		{
			len--;
			bloc1[len] = bloc2[len];
		}
	}
	else
	{
		i = 0;
		while (i++ < len)
			bloc1[i - 1] = bloc2[i - 1];
	}
	return (dest);
}
