/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:26:45 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/13 18:54:11 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static bool	validate_rows(const t_game *game)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(game->buffer[0]))
	{
		if (game->buffer[0][i] != '1')
			return (false);
		i += 1;
	}
	i = 0;
	while (i < ft_strlen(game->buffer[game->cols - 1]))
	{
		if (game->buffer[game->cols - 1][i] != '1')
			return (false);
		i += 1;
	}
	return (true);
}

static bool	validate_cols(const t_game *game)
{
	size_t	i;
	size_t	len_row;

	i = 0;
	while (i < game->cols)
	{
		if (game->buffer[i][0] != '1')
			return (false);
		i += 1;
	}
	i = 0;
	while (i < game->cols)
	{
		len_row = ft_strlen(game->buffer[i]);
		if (game->buffer[i][len_row - 1] != '1')
			return (false);
		i += 1;
	}
	return (true);
}

static bool validate_directions(t_game *game)
{
	size_t	i;
	size_t	j;
	size_t	c_directions;

	i = 0;
	j = 0;
	c_directions = 0;
	while (game->buffer[i])
	{
		j = 0;
		while (game->buffer[i][j])
		{
			if (is_cardinal_direction(game->buffer[i][j]))
				c_directions += 1;
			j += 1;
		}
		i += 1;
	}
	if (c_directions != 1)
		return (false);
	return (true);
}

bool	is_valid_map(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!game->buffer || !validate_rows(game) || !validate_cols(game)
		|| !validate_directions(game) || !validate_identifiers(game))
		return (false);
	while (game->buffer[i])
	{
		j = 0;
		while (game->buffer[i][j])
		{
			if (!verify_char(game->buffer[i][j]))
				return (false);
			j += 1;
		}
		i += 1;
	}
	return (true);
}
