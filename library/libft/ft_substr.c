/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 00:33:21 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/18 16:12:27 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s8;

	if (!s || start >= ft_strlen(s))
	{
		s8 = (char *)malloc(1);
		if (s8)
			s8[0] = '\0';
		return (s8);
	}
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start;
	}
	s8 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s8)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		s8[i] = s[start + i];
		i++;
	}
	s8[i] = '\0';
	return (s8);
}
