/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hprudhom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:53:11 by hprudhom          #+#    #+#             */
/*   Updated: 2021/01/19 15:32:24 by hprudhom         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		x;
	char				*dst;
	size_t				len_s;

	len_s = len;
	if (start > (unsigned int)ft_strlen(s) - 1)
	{
		if (!(dst = malloc(sizeof(char))))
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	if ((size_t)start + len > (size_t)ft_strlen(s))
		len_s = (size_t)ft_strlen(s) - (size_t)start;
	if (!(dst = malloc(sizeof(char) * (len_s + 1))))
		return (NULL);
	x = 0;
	while (x < len_s)
	{
		dst[x] = s[start];
		x++;
		start++;
	}
	dst[x] = '\0';
	return (dst);
}

static char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		x;
	int		y;

	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x])
	{
		str[y] = s1[x];
		y++;
		x++;
	}
	x = 0;
	while (s2[x])
	{
		str[y] = s2[x];
		y++;
		x++;
	}
	str[y] = '\0';
	return (str);
}

static int			ft_breakline(char **src, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*src)[len] != '\n' && (*src)[len] != '\0')
		len++;
	if ((*src)[len] == '\n')
	{
		*line = ft_substr(*src, 0, len);
		tmp = ft_strdup(&((*src)[len + 1]));
		free(*src);
		*src = tmp;
		if ((*src)[0] == '\0')
		{
			ft_strdel(src);
		}
	}
	else
	{
		*line = ft_strdup(*src);
		ft_strdel(src);
		return (0);
	}
	return (1);
}

static int			ft_verif(char **src, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && src[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (ft_breakline(&src[fd], line));
}

int					get_next_line(int fd, char **line)
{
	int				ret;
	static char		*src[4096];
	char			buf[BUFFER_SIZE + 1];
	char			*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (src[fd] == NULL)
			src[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(src[fd], buf);
			free(src[fd]);
			src[fd] = tmp;
		}
		if (ft_strchr(src[fd], '\n'))
			break ;
	}
	return (ft_verif(src, line, ret, fd));
}
