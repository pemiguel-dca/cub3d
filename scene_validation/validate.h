/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:30:08 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:23:16 by pemiguel         ###   ########.fr       */
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

typedef struct validate
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_validate;

size_t	get_cols(const char **map);
size_t	get_first_occur_row(const char **map, size_t row);
size_t	get_last_occur_row(const char **map, size_t row);

/*validate_map.c*/

bool	valid_map(const char **map);
bool	right_wall(const char **map, size_t i, size_t j);
bool	left_wall(const char **map, size_t i, size_t j);
bool	down_wall(const char **map, size_t i, size_t j);
bool	up_wall(const char **map, int i, size_t j);

static inline bool	surrounded_by_walls(const char **map, size_t y, size_t x)
{
	if (x == get_first_occur_row(map, y)
		|| x == get_last_occur_row(map, y)
		|| y == 0 || y == get_cols(map) - 1)
		return (false);
	if (!right_wall(map, y, x) || !left_wall(map, y, x)
		|| !up_wall(map, y, x) || !down_wall(map, y, x))
		return (false);
	return (true);
}

/*validate.c*/

bool	valid_args(int fd, size_t args, const char *file_name);
bool	valid_buffer(const char **buffer);
bool	valid_scene(char **buffer);

static inline bool	has_extension(const char *path)
{
	char	*sub;

	sub = ft_strrchr(path, '.');
	return (sub && ft_strlen(sub + 1) == sizeof(EXTENSION) - 1
		&& !ft_strncmp(sub + 1, EXTENSION, sizeof(EXTENSION) - 1));
}

/*validate_settings*/

static inline size_t	get_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i += 1;
	return (i);
}

static inline bool	only_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i += 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i += 1;
	}
	return (true);
}

bool	valid_settings(char **buffer);

#endif
