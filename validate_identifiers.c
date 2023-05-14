/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_identifiers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:13:57 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/14 17:09:26 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	validate_rgb_codes(char *str)
{
	char	**rgb_codes;
	size_t	i;

	rgb_codes = ft_split(str, ',');
	i = 0;
	while (rgb_codes[i])
	{
		if (ft_atoi(rgb_codes[i]) < 0 || ft_atoi(rgb_codes[i]) > 255)
		{
			free_2Darrays(rgb_codes);
			return (false);
		}
		i += 1;
	}
	free_2Darrays(rgb_codes);
	return (true);
}

static size_t	get_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i += 1;
	return (i);
}

static char	**get_types(t_game *game)
{
	char	**types;
	size_t	i;

	types = malloc((N_TYPES + 1) * sizeof(char *));
	i = 0;
	while (game->identifiers[i])
	{
		types[i] = ft_substr(game->identifiers[i], 0,
				get_len(game->identifiers[i]));
		i += 1;
	}
	types[i] = 0;
	return (types);
}

bool	validate_identifiers(t_game *game)
{
	size_t	i;
	char	**types;

	types = get_types(game);
	i = 4;
	while (game->identifiers[i])
	{
		if (!validate_types(types)
			|| !validate_rgb_codes(game->identifiers[i]
				+ ft_strlen(types[i])))
		{
			free_2Darrays(types);
			return (false);
		}
		i += 1;
	}
	free_2Darrays(types);
	return (true);
}
