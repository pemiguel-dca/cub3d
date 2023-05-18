/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:30:08 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 12:45:09 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_H
# define VALIDATE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define ACCEPTABLE_CHARS "01NSEW "
# define EXTENSION "cub"
# define N_SETTINGS 6

typedef struct
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_validate;

/*validate_map.c*/

bool	valid_map(const char **map);

static inline size_t	get_cols(const char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		i += 1;
	return (i);
}

static inline size_t	get_first_occur_row(const char **map, size_t row)
{
	size_t	i;

	i = 0;
	while (map[row][i] && ft_isspace(map[row][i]))
		i += 1;
	return (i);
}

static inline size_t	get_last_occur_row(const char **map, size_t row)
{
	size_t	i;

	i = ft_strlen(map[row]) - 1;
	while (map[row][i] && ft_isspace(map[row][i]))
		i -= 1;
	return (i);
}

/*validate.c*/

bool	valid_args(int fd, size_t args, const char *file_name);
bool	valid_buffer(const char **buffer);
bool	valid_scene(char **buffer);

static inline bool is_cardinal_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static inline bool	has_extension(const char *path)
{
	char	*sub;

	sub = ft_strrchr(path, '.');
	return (sub && ft_strlen(sub + 1) == sizeof(EXTENSION) - 1
		&& !ft_strncmp(sub + 1, EXTENSION, sizeof(EXTENSION) - 1));
}

/*validate_settings*/

bool	valid_settings(char **buffer);

#endif
