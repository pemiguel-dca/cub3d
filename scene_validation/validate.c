/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:26:45 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/21 13:47:52 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	valid_args(int fd, size_t args, const char *file_name)
{
	char	*msg;

	if (args != 2 || !has_extension(file_name))
		return (error_msg(SYNTAX));
	if (fd == -1)
	{
		msg = ft_strjoin(OPENING_FILE, file_name);
		error_msg(msg);
		free(msg);
		return (false);
	}
	return (true);
}

bool	valid_buffer(const char **buffer)
{
	size_t	buf_len;

	if (!buffer)
		return (error_msg(EMPTY_FILE));
	buf_len = 0;
	while (buffer[buf_len])
		buf_len += 1;
	if (buf_len < 7)
		return (error_msg(WRONG_FORMAT));
	return (true);
}

static bool	valid_char(char to_verify)
{
	size_t	i;

	i = 0;
	while (ACCEPTABLE_CHARS[i])
	{
		if (to_verify == ACCEPTABLE_CHARS[i])
			return (true);
		i += 1;
	}
	return (false);
}

bool	valid_scene(char **buffer)
{
	size_t	i;
	size_t	j;
	size_t	c_directions;

	if (!valid_settings(buffer)
		|| !valid_map((const char **)buffer + N_SETTINGS))
		return (false);
	i = N_SETTINGS;
	c_directions = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i][j])
		{
			if (!valid_char(buffer[i][j]))
				return (error_msg(INVALID_CHAR));
			if (is_cardinal_direction(buffer[i][j]))
				c_directions += 1;
			j += 1;
		}
		i += 1;
	}
	if (c_directions != 1)
		return (error_msg(ONE_PLAYER));
	return (true);
}
