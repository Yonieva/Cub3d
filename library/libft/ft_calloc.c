/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:05:46 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/09 03:01:11 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elements, size_t size)
{
	void	*ptr;
	int		result;

	ptr = malloc(elements * size);
	result = elements * size;
	if (ptr == NULL)
	{
		return (ptr);
	}
	ft_bzero(ptr, result);
	return (ptr);
}
