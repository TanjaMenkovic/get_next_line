/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:00:05 by tmenkovi          #+#    #+#             */
/*   Updated: 2023/11/22 18:00:40 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	shift_buff(char *buff, size_t from)
{
	int		i;

	i = 0;
	while (buff[from + i] != 0)
	{
		buff[i] = buff[from + i];
		i++;
	}
	buff[i] = 0;
}

char	*get_next_line_concat(char **str, char *buff)
{
	char	*tmp_str;

	tmp_str = fn_strjoin(*str, buff);
	free(*str);
	if (!tmp_str)
		return (NULL);
	*str = fn_strjoin("", tmp_str);
	free(tmp_str);
	if (!*str)
		return (NULL);
	return (*str);
}

char	*get_next_line_init(char **str, int fd, char *buff, int *line_size)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*line_size = 0;
	*str = fn_strjoin("", buff);
	if (!str)
		return (NULL);
	return (*str);
}

char	*next_line_parse(int line_size, int new_line, char *buff, char **str)
{
	if (new_line != -1)
	{
		shift_buff(buff, fn_str_index(buff, '\n') + 1);
		*(*str + new_line + 1) = 0;
	}
	else
		buff[0] = 0;
	if (line_size == -1)
	{
		free(*str);
		return (NULL);
	}
	if (line_size == 0 && fn_strlen(*str) == 0)
	{
		free(*str);
		return (NULL);
	}
	return (resize_str(*str));
}

char	*get_next_line(int fd)
{
	char				*str;
	char				*tmp_buff;
	int					line_size;
	int					new_line;
	static char			buff[OPEN_FILES_MAX][BUFFER_SIZE + 1];

	if (fd >= OPEN_FILES_MAX)
		return (NULL);
	tmp_buff = (char *)buff[fd];
	if (!get_next_line_init(&str, fd, tmp_buff, &line_size))
		return (NULL);
	new_line = fn_str_index(str, '\n');
	while (new_line == -1)
	{
		line_size = read(fd, tmp_buff, BUFFER_SIZE);
		if (line_size <= 0)
			break ;
		tmp_buff[line_size] = 0;
		if (!get_next_line_concat(&str, tmp_buff))
			return (NULL);
		new_line = fn_str_index(str, '\n');
	}
	return (next_line_parse(line_size, new_line, tmp_buff, &str));
}
