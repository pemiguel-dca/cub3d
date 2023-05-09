/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:26:45 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/09 17:08:02 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "cub3d.h"

#include <stdio.h>
static bool	verify_char(char to_verify)
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

static bool	validate_bounds(const t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->cols)
	{
		j = 0;
		while (j < game->rows)
		{
			if (
				(
					i == 0 ||
					j == 0 ||
					i == game->rows ||
					j == game->cols
				) &&
				game->buffer[i][j] != '1'
			)
				return (false);
			j += 1;
		}
		i += 1;
	}
	return (true);
}

#include <stdio.h>
bool	is_valid_map(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->cols)
	{
		j = 0;
		while (j < game->rows)
		{
			if (!verify_char(game->buffer[i][j]))
				return (false);
			j += 1;
		}
		i += 1;
	}
	if (!validate_bounds(game))
		return (false);
	return (true);
}

