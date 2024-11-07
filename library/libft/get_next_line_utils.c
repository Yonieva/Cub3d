/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:42:41 by yonieva           #+#    #+#             */
/*   Updated: 2023/11/10 19:47:21 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strgnl(char *s, int c)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*joiny;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	joiny = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joiny)
		return (0);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			joiny[i] = s1[i];
	while (s2[j])
		joiny[i++] = s2[j++];
	joiny[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (joiny);
}
