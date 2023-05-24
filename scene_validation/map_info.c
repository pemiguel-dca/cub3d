/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:22:57 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"

size_t	get_cols(const char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		i += 1;
	return (i);
}

size_t	get_first_occur_row(const char **map, size_t row)
{
	size_t	i;

	i = 0;
	while (map[row][i] && ft_isspace(map[row][i]))
		i += 1;
	return (i);
}

size_t	get_last_occur_row(const char **map, size_t row)
{
	size_t	i;

	i = ft_strlen(map[row]) - 1;
	while (map[row][i] && ft_isspace(map[row][i]))
		i -= 1;
	return (i);
}
