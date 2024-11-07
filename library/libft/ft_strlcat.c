/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:55:15 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/18 13:56:06 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = dest_len;
	j = 0;
	if (destsize <= dest_len)
		return (destsize + src_len);
	while (src[j] != '\0' && i < destsize - 1)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}

/*
#include <stdio.h>

int main ()
{
	char	*str123;
	char	*str234;

	str1 = "Salut";
	str2 = "Ca va ?";
	printf("Ma fonction : %ld\n", ft_strlcat(str234, str123, 5));
	printf("La fonction strlcat : %ld\n", strlcat(str234, str123, 5));
}
*/
