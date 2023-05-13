/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:59:06 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/13 18:14:38 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_spaces(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			str[j] = str[i];
			j += 1;
		}
		i += 1;
	}
	str[j] = '\0';
}

void	parse_map(t_game *game)
{
	size_t	i;

	i = 0;
	if (!game->buffer)
		return ;
	while (game->buffer[i])
	{
		trim_spaces(game->buffer[i]);
		i += 1;
	}
}
