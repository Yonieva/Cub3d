/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:24:12 by yonieva           #+#    #+#             */
/*   Updated: 2023/11/08 18:20:12 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count = count + print_char(va_arg(args, int));
	else if (specifier == 's')
		count = count + print_str(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		count = count + print_nbr((long)va_arg(args, int), 10);
	else if (specifier == 'u')
		count = count + print_nbr((long)va_arg(args, unsigned int), 10);
	else if (specifier == 'p')
		count = count + print_ptr(va_arg(args, void *));
	else if (specifier == 'x')
		count = count + print_nbr((long)va_arg(args, unsigned int), 16);
	else if (specifier == 'X')
		count = count + printxup((long)va_arg(args, unsigned int), 16);
	else
		count = count + print_char(specifier);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count = count + print_format(format[i++], args);
		}
		else
		{
			count = count + print_char(format[i]);
			i++;
		}
	}
	va_end(args);
	return (count);
}

/*
#include <stdio.h>
int	main()
{
	int testint;
	int	test_neg_int;
	int	testhexa;
	int testhexaup;
	char testchar;
	char *teststr;
	unsigned int	testu;
	
	testint = 142;
	test_neg_int = -2147483648;
	testhexa = 1968;
	testhexaup = 1968;
	testchar = 'c';
	teststr = "Salut Bg !";
	testu = 3435;

	ft_printf("test de ma fonction avec un int : %d\n", testint);
	printf("test de la vrai fonction avec un int : %d\n\n", testint);
    ft_printf("test de ma fonction avec un int neg : %d\n", test_neg_int);
    printf("test de la vrai fonction avec un int neg : %d\n\n", test_neg_int);
    ft_printf("test de ma fonction avec un char : %c\n", testchar);
    printf("test de la vrai fonction avec un char : %c\n\n", testchar);
    ft_printf("test de ma fonction avec une string : %s\n", teststr);
    printf("test de la vrai fonction avec une string : %s\n\n", teststr);
 	ft_printf("test de ma fonction avec un hexa : %x\n", testhexa);
    printf("test de la vrai fonction avec un hexa : %x\n\n", testhexa);
    ft_printf("test de ma fonction avec un hexa  upper: %X\n", testhexaup);
    printf("test de la vrai fonction avec un hexa upper : %X\n\n", testhexaup);
    ft_printf("test de ma fonction avec un decimal non signe : %u\n", testu);
    printf("test de la vrai ft avec un decimal non signe : %u\n\n", testu);
    	int *ptr;
	int n;
	int count;
	ptr = &n;
	count = 0;
	printf("--Real printf\n");
	count += printf("%p\n", ptr);
	printf("%d\n", count);
	count = 0;
	printf("--My printf\n");
	count += ft_printf("%p\n", ptr);
	printf("%d\n", count);
	count = 0;
	printf("|| Null case || \n--Real printf\n");
	count += printf("%p\n", 0);
	printf("%d\n", count);
	count = 0;
	printf("My printf\n");
	count += ft_printf("%p\n", 0);
	printf("%d\n", count);
	count = 0;
}
*/
