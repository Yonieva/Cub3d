/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:18:14 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/18 14:24:27 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t			str_len;
	char			*ptr;
	unsigned char	nb;

	nb = (unsigned char)c;
	str_len = ft_strlen(str);
	ptr = (char *)str;
	if (nb == '\0')
		return (ptr + ft_strlen(str));
	while (str_len > 0)
	{
		if ((unsigned char)ptr[str_len - 1] == nb)
		{
			return (ptr + str_len - 1);
		}
		str_len--;
	}
	return (NULL);
}
