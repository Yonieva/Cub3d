/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:36:32 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/12 20:38:40 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (str[start] != '\0' && ft_strchr(set, str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end > 0 && ft_strchr(set, str[end]))
		end--;
	return (ft_substr(str, start, end - start + 1));
}
