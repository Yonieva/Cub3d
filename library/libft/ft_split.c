/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:36:10 by yonieva           #+#    #+#             */
/*   Updated: 2023/10/14 00:50:47 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countword(const char *str, char c)
{
	int	count;
	int	yes;
	int	i;

	i = 0;
	count = 0;
	yes = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && yes == 0)
		{
			yes = 1;
			count++;
		}
		else if (str[i] == c)
		{
			yes = 0;
		}
		i++;
	}
	return (count);
}

static char	*mallocword(const char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**arr;
	int		len;
	int		i;

	len = countword(str, c);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			arr[i] = mallocword(str, c);
			if (!arr[i])
				return (ft_free(arr, i));
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
