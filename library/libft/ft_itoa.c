/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:50:11 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/17 16:23:40 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	if (nb == 0)
	{
		count++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char	*ft_malloc(int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int nb)
{
	int		len;
	char	*result;

	len = int_len(nb);
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	result = ft_malloc(len);
	if (!result)
		return (NULL);
	if (nb < 0 && nb != -2147483648)
	{
		result[0] = '-';
		nb = -nb;
	}
	else if (nb == 0)
	{
		result[0] = '0';
	}
	while (nb > 0)
	{
		len--;
		result[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (result);
}
