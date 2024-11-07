/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:41:22 by yonieva           #+#    #+#             */
/*   Updated: 2023/11/08 18:21:23 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(int c)
{
	return (write(1, &c, 1));
}

int	print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		print_char((int)str[i]);
		i++;
	}
	return (i);
}

int	print_nbr(long n, int base)
{
	int		count;
	char	*base16;

	base16 = "0123456789abcdef";
	if (n < 0)
	{
		print_char('-');
		return (print_nbr(-n, base) + 1);
	}
	else if (n < base)
		return (print_char(base16[n]));
	else
	{
		count = print_nbr(n / base, base);
		return (count + print_nbr(n % base, base));
	}
}

int	printxup(long n, int base)
{
	int		count;
	char	*base16;

	count = 0;
	base16 = "0123456789ABCDEF";
	if (n < 0)
	{
		print_char('-');
		return (printxup(-n, base) + 1);
	}
	else if (n < base)
		return (print_char(base16[n]));
	else
	{
		count = count + printxup(n / base, base);
		return (count + printxup(n % 16, base));
	}
}

int	print_ptr(void *ptr)
{
	unsigned long	pt;
	int				count;

	count = 0;
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	pt = (unsigned long)ptr;
	if (pt > 15)
	{
		count = count + print_ptr((void *)(pt / 16));
	}
	else
	{
		print_str("0x");
		count = count + 2;
	}
	count = count + print_char("0123456789abcdef"[pt % 16]);
	return (count);
}
