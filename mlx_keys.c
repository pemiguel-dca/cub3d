/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:00:24 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 12:18:58 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	top_right(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
}

int	keys_pressed(int key, t_game *game)
{
	if (key == ESC)
	{
		free_game(game);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
