/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:43 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 15:40:41 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# include "libft/libft.h"

# define ERROR "Error: "
# define OPENING_FILE "Cannot open file: "
# define SYNTAX "Syntax: ./cub3d <*.cub>"
# define ONE_PLAYER "Map must have ONE player"
# define OPEN_TEXTURE "Cannot open texture"
# define WRONG_FORMAT "Wrong format"
# define EMPTY_FILE "File is empty"
# define RGB_FORMAT "RGB format: [0, 255], [0, 255], [0, 255]"
# define SETTINGS "Wrong settings format"
# define MAP_WALLS "Map is not surrounded by walls"
# define INVALID_CHAR "Map has an invalid char"

static inline bool	error_msg(char *str)
{
	str = ft_strjoin(ERROR, str);
	ft_putstr_fd(str, STDERR_FILENO);
	free(str);
	return (false);
}

#endif
