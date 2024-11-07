/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:01:57 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/05 18:49:50 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t nb)
{
	size_t	i;
	char	*str1;

	i = 0;
	str1 = (void *)str;
	while (i < nb)
	{
		if (str1[i] == (char) c)
			return (&str1[i]);
		i++;
	}
	return (NULL);
}
