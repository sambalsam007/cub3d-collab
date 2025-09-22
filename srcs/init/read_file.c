/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:57:19 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/04 18:26:54 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// static void	free_all(char *s1, char *s2)
// {
// 	if (s1)
// 		free(s1);
// 	if (s2)
// 		free(s2);
// }

static char	*append_line(char *content, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(content, line);
	free(content);
	free(line);
	return (tmp);
}

char	*read_file(const char *file)
{
	int		fd;
	char	*line;
	char	*content;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (err_msg(ERR_FILE), NULL);
	content = ft_strdup("");
	if (!content)
		return (err_msg(ERR_MAL), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		content = append_line(content, line);
		if (!content)
			return (close(fd), err_msg(ERR_MAL), NULL);
	}
	close(fd);
	return (content);
}
