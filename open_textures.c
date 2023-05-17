/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:25:00 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/17 18:05:21 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	steps_to_path(const char *setting)
{
	size_t	i;

	i = 0;
	while (setting[i])
	{
		if (setting[i] == 32)
			break ;
		i += 1;
	}
	return (ft_skip_spaces(setting + i));
}

bool	open_textures(t_data *img, t_game *game)
{
	size_t	i;

	i = 0;
	while (game->settings[i])
	{
		
		i += 1;
	}
}
