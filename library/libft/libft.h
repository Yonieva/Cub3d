/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonieva <yonieva@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:58:11 by yonieva           #+#    #+#             */
/*   Updated: 2024/11/25 18:52:31 by yonieva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# define BUFFER_SIZE 1
/*--------------------------------AFFICHAGE-----------------------------------*/
void	ft_putchar_fd(char c, int fd);/*affiche char c sur sortie fd*/
void	ft_putstr_fd(char *str, int fd);/*affcihe str sur sortie fd*/
void	ft_putendl_fd(char*str, int fd);/*affiche str + '\n' sur sortie fd*/
void	ft_putnbr_fd(int nb, int fd);/*affiche tous les int possible sur fd*/
/*----------------------------------------------------------------------------*/
/*--------------------------------FT_PRINTF-----------------------------------*/
int		print_char(int c);
int		print_str(char *str);
int		print_nbr(long n, int base);
int		printxup(long n, int base);
int		print_ptr(void *ptr);
int		print_format(char specifier, va_list args);
int		ft_printf(const char *format, ...);
/*----------------------------------------------------------------------------*/
/*-----------------------------GET NEXT LINE---------------------------------*/
char	*get_next_line(int fd);
char	*ft_line_results(int ret, char *stock, char *buffer);
void	ft_get_the_spare(char *buffer);
char	*ft_get_the_line(char *stock);
int     ft_malloc_count(char *stock);
char	*f_strjoin(char *s1, char *s2);
char	*f_strdup(char *s1);
char	*f_strchr(char *s, int c);
/*---------------------------------------------------------------------------*/
/*----------------TRAITEMENT CARACTERES ET CHAINE DE CARACTERES---------------*/
size_t	ft_strlen(const char *str);/*Retourne nb char d une string*/
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);/*cpy src>des*/
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);/*cat src>des*/
int		ft_isalpha(int c);/*Return vrai si 'c' est alpha sinon faux*/
int		ft_isdigit(int c);/*Return vrai si 'c' est numeric sinon faux*/
int		ft_isalnum(int c);/*Return vrai si 'c' est alphanum sinon faux*/
int		ft_isascii(int c);/*Return vrai si 'c' est dans la tabl ascii*/
int		ft_isprint(int c);/*Return vrai si 'c' est imprimable*/
int		ft_tolower(int c);/*Return 'c' en miniscule, sinon return 'c'*/
int		ft_toupper(int c);/*Return 'c' en majuscule, sinon return 'c'*/
int		ft_strncmp(const char *str1, const char *str2, size_t nb);/*Cm*/
char	*ft_strdup(const char *src);/*dup newstring avec malloc*/
char	*ft_strchr(const char *str, int c);/*Pointe 'c' ds str,return suite*/
char	*ft_strrchr(const char *str, int c);/*Pointe derniere occ de c ds str*/
char	*ft_substr(const char *s, unsigned int start, size_t len);/*dup substr*/
char	*ft_strjoin(char *s1, const char *s2);/*cat s1+s2 ds un newstr*/
char	*ft_strtrim(char const *str, const char *set);/*sup dbt et fin set/str*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
/*recherche needle dans haystack len fois et retourne a partir de needle*/
char	**ft_split(char const *str, char c);/*fait un tableau de mot selon sep*/
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
/*applique la ft 'fd' sur chq char de la string 's' et rtrn new string*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/*aplique la ft 'fd' sur chq char de la string 's', ne return rien*/
/*----------------------------------------------------------------------------*/
/*---------------------------GESTION DE LA MEMOIRE----------------------------*/
void	ft_bzero(void *blocmem, size_t nb);/*rempli blc de 0, nb de fois*/
void	*ft_calloc(size_t elements, size_t size);/*aloue ele * siz et init a 0*/
void	*ft_memset(void *blocmem, int c, size_t len);/*rempl blc de c, ln de x*/
void	*ft_memchr(const void *str, int c, size_t nb);/*retrn 1e & de c ds str*/
void	*ft_memcpy(void *dest, const void *src, size_t nb);/*cpy src dans dest*/
void	*ft_memmove(void *dest, const void *src, size_t len);/*!chevauchement!*/
int		ft_memcmp(const void *str1, const void *str2, size_t nb);/*cmp 2 bloc*/
/*----------------------------------------------------------------------------*/
/*--------------------------------CONVERSIONS---------------------------------*/
int		ft_atoi(const char *str);/*Convert les char nbrs dans une str en int*/
char	*ft_itoa(int nb);/*Convert int en char dans une nouvelle string*/
/*----------------------------------------------------------------------------*/
#endif