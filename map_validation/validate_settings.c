/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:13:57 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 21:59:33 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	only_digits(char *str)
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

static bool	validate_types(char **settings)
{
	t_validate	val;
	size_t		i;

	i = 0;
	val = (t_validate){.no = 0, .so = 0, .we = 0, .ea = 0, .f = 0, .c = 0};
	while (settings[i])
	{
		if (ft_strcmp(settings[i], "NO") == 0 || (ft_strcmp(settings[i], "N") == 0 && ft_strlen(settings[i]) == 1))
			val.no += 1;
		else if (ft_strcmp(settings[i], "SO") == 0 || (ft_strcmp(settings[i], "S") == 0 && ft_strlen(settings[i]) == 1))
			val.so += 1;
		else if (ft_strcmp(settings[i], "WE") == 0 || (ft_strcmp(settings[i], "W") == 0 && ft_strlen(settings[i]) == 1))
			val.we += 1;
		else if (ft_strcmp(settings[i], "EA") == 0 || (ft_strcmp(settings[i], "E") == 0 && ft_strlen(settings[i]) == 1))
			val.ea += 1;
		else if (ft_strcmp(settings[i], "F") == 0)
			val.f += 1;
		else if (ft_strcmp(settings[i], "C") == 0)
			val.c += 1;
		i += 1;
	}
	return (val.no == 1 && val.so == 1 && val.we == 1
			&& val.ea == 1 && val.f == 1 && val.c == 1);
}

static bool	validate_rgb_codes(char *str)
{
	char	**rgb_codes;
	size_t	i;

	rgb_codes = ft_split(str, ',');
	i = 0;
	while (rgb_codes[i])
	{
		if (ft_atoi(rgb_codes[i]) < 0 || ft_atoi(rgb_codes[i]) > 255
			|| !only_digits(rgb_codes[i]))
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

	types = malloc((N_SETTINGS + 1) * sizeof(char *));
	i = 0;
	while (game->settings[i])
	{
		types[i] = ft_substr(game->settings[i], 0,
				get_len(game->settings[i]));
		i += 1;
	}
	types[i] = 0;
	return (types);
}

bool	validate_settings(t_game *game)
{
	size_t	i;
	char	**types;

	types = get_types(game);
	i = 0;
	while (game->settings[i])
	{
		if (!validate_types(types)
			|| ((game->settings[i][0] == 'F' || game->settings[i][0] == 'C') 
			&& !validate_rgb_codes(game->settings[i] + ft_strlen(types[i]))))
		{
			free_2Darrays(types);
			return (false);
		}
		i += 1;
	}
	free_2Darrays(types);
	return (true);
}
