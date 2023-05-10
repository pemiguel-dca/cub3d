/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:26:45 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/09 21:50:58 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Provavelmente a verificacao esta toda mal pois o mapa pode nao ter o mesmo tamanho para cada linha
Logo a condicao i < game->cols nem sempre e verdade*/
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
	while (i < game->rows)
	{
		if (game->buffer[0][i] != '1')
			return (false);
		i += 1;
	}
	i = 0;
	while (i < game->rows)
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
		if (game->buffer[i][game->rows - 1] != '1')
			return (false);
		i += 1;
	}
	return (true);
}

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
	if (!validate_rows(game) || !validate_cols(game))
		return (false);
	return (true);
}
