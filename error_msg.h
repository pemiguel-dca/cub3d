/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:43 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/17 17:23:37 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# include "libft/libft.h"

# define ERROR "error: "
# define OPEN_TEXTURE "Cannot open the texture\n"
# define WRONG_FORMAT "Wrong format\n"
# define EMPTY_FILE "File is empty\n"
# define RGB_FORMAT "RGB format: [0, 255], [0, 255], [0, 255]\n"
# define SETTINGS "Wrong settings format\n"
# define MAP_WALLS "Map is not surrounded by walls\n"
# define INVALID_CHAR "Map has an invalid char\n"
# define CANT_MOVE "Player can't move\n"

static inline bool	error_msg(char *str)
{
	//bad pointer here suposedly
	str = ft_strjoin(ERROR, str);
	ft_putstr_fd(str, STDERR_FILENO);
	free(str);
	return (false);
}

static inline bool	good_buffer(const char **buffer)
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

#endif
