/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:44 by tmenkovi          #+#    #+#             */
/*   Updated: 2023/11/21 15:44:42 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_FILES_MAX
/* this can be found as _SC_OPEN_MAX or FOPEN_MAX (standard library) */
/* as limit of max open files - default 4096 but for performace we use 16 */
#  define OPEN_FILES_MAX 16
# endif

// /* get_next_line_utils_bonus.c */
char	*fn_strjoin(char *s1, char *s2);
int		fn_str_index(const char *s, int character);
size_t	fn_strlen(const char *s);
char	*resize_str(char *str);

/* get_next_line_bonus.c */
char	*get_next_line_concat(char **str, char *buff);
char	*get_next_line_init(char **str, int fd, char *buff, int *line_size);
char	*next_line_parse(int line_size, int new_line, char *buff, char **str);
char	*get_next_line(int fd);

#endif