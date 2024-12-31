/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:05:46 by yonieva           #+#    #+#             */
/*   Updated: 2024/12/31 18:36:18 by gaesteve         ###   ########.fr       */
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
