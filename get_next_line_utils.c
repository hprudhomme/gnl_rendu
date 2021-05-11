/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:59:41 by hprudhom          #+#    #+#             */
/*   Updated: 2021/01/19 15:08:38 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	if (!(str = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = ft_strlen(s);
	while (*s != '\0')
		*str++ = *s++;
	*str = '\0';
	return (str - i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char*)s);
	return (NULL);
}

void	ft_strdel(char **as)
{
	if (as != NULL && *as != NULL)
	{
		if ((void**)as != NULL)
		{
			free(*(void**)as);
			*(void**)as = NULL;
		}
	}
}
