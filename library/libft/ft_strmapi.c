/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:18:35 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/18 15:18:41 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	result = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	i = 0;
	if (!result)
		return (NULL);
	while (i < ft_strlen(s))
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
#include <ctype.h>
int main() {
    const char *input = "Hello, World!";
    
    // Utilisation de la fonction ft_strmapi pour convertir en majuscules
    char *result = ft_strmapi(input, toupper);

    if (result) {
        printf("Chaîne d'entrée : %s\n", input);
        printf("Chaîne en majuscules en appelant ft_toupper : %s\n", result);

        free(result);
    } else {
        printf("Échec de l'allocation mémoire.\n");
    }

    return 0;
}
*/
