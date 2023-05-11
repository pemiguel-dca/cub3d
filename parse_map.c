/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:59:06 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/11 17:52:45 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i += 1;
	}
	return (false);
}

void	trim_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		//if ()trim
		i += 1;
	}
}

void	parse_map(t_game *game)
{
	size_t	i;

	i = 0;
	while (game->buffer[i])
	{
		if (has_spaces(game->buffer[i]))
			trim_spaces();
		i += 1;
	}
}
