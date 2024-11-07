/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:01:59 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/06 11:02:09 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1,	const void *str2, size_t nb)
{
	unsigned char	*temp1;
	unsigned char	*temp2;
	int				i;

	temp1 = (unsigned char *)str1;
	temp2 = (unsigned char *)str2;
	i = 0;
	while (nb > 0)
	{
		if (temp1[i] != temp2[i])
		{
			return (temp1[i] - temp2[i]);
		}
		i++;
		nb--;
	}
	return (0);
}
