/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:04:28 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:28:44 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_darrays(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i += 1;
	}
	free(array);
}

void	free_game(t_game *game)
{
	if (game->map)
		free_darrays(game->map);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
	}
}
