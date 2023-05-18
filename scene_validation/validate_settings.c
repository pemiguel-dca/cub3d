/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:13:57 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 17:10:48 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	validate_textures(char *path)
{
	int		w;
	int		h;
	void	*mlx_tmp;
	void	*texture;

	mlx_tmp = mlx_init();
	w = WIDTH;
	h = HEIGHT;
	texture = mlx_xpm_file_to_image(mlx_tmp, path, &w, &h);
	if (!texture)
	{
		free(mlx_tmp);
		return (error_msg(OPEN_TEXTURE));
	}
	free(mlx_tmp);
	free(texture);
	return (true);
}

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
	if (!(val.no == 1 && val.so == 1 && val.we == 1
			&& val.ea == 1 && val.f == 1 && val.c == 1))
		return (error_msg(SETTINGS));
	return (true);
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
			return (error_msg(RGB_FORMAT));
		}
		i += 1;
	}
	free_2Darrays(rgb_codes);
	if (i != 3)
		return (error_msg(RGB_FORMAT));
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

static char	**get_types(char **settings)
{
	char	**types;
	size_t	i;

	types = malloc((N_SETTINGS + 1) * sizeof(char *));
	i = 0;
	while (settings[i])
	{
		types[i] = ft_substr(settings[i], 0,
				get_len(settings[i]));
		i += 1;
	}
	types[i] = NULL;
	return (types);
}

bool	valid_settings(char **buffer)
{
	size_t	i;
	char	**types;

	types = get_types(buffer);
	i = 0;
	while (i < N_SETTINGS)
	{
		if (!validate_types(types) || ((buffer[i][0] == 'F' || buffer[i][0] == 'C')
			&& !validate_rgb_codes(buffer[i] + 1 + ft_strlen(types[i])))
			|| ((buffer[i][0] != 'F' && buffer[i][0] != 'C')
			&& !validate_textures((buffer[i] + ft_strlen(types[i])+ ft_skip_spaces(buffer[i] + ft_strlen(types[i]))))))
		{
			free_2Darrays(types);
			return (false);
		}
		i += 1;
	}
	free_2Darrays(types);
	return (true);
}
