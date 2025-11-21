/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:53:09 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/04 16:07:44 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*ft_beforenl(char *s)
{
	size_t	len;
	char	*line;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
		len++;
	line = ft_strndup(s, len);
	return (line);
}

static char	*ft_afternl(char *s)
{
	size_t	len;
	char	*nexttime;

	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\0')
		return (free(s), NULL);
	len++;
	nexttime = ft_strndup(s + len, ft_strlen(s + len));
	return (free(s), nexttime);
}

static void	free_static(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

static char	*agency(int fd, char *line, char *buf)
{
	ssize_t	bytes_read;
	char	*new_line;

	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		new_line = ft_strjoin(line, buf);
		if (!new_line)
			return (free(line), NULL);
		free(line);
		line = new_line;
		if (ft_strchr(line, '\n'))
			break ;
	}
	if (bytes_read == -1)
		return (free(line), NULL);
	if (!line || *line == '\0')
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*nexttime;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_static(&nexttime), NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_static(&nexttime), NULL);
	if (!nexttime)
		nexttime = ft_strndup("", 0);
	if (!nexttime)
		return (free(buf), free_static(&nexttime), NULL);
	nexttime = agency(fd, nexttime, buf);
	free(buf);
	if (!nexttime)
		return (free_static(&nexttime), NULL);
	line = ft_beforenl(nexttime);
	nexttime = ft_afternl(nexttime);
	return (line);
}
