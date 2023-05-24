/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:19:24 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:41:18 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# define TEXTURE_WIDTH 	64
# define TEXTURE_HEIGHT 64

# include "raycaster.h"

t_data	create_textures(void *sprite);
size_t	get_texture_x(t_raycaster *rc, t_dda *dda, t_game *game);
int		get_texture_pixel(t_texture *texture);

// looking at direction should display 'opposite' direction
// seeing same sprite s and n
static inline t_data	*get_respective_texture(t_game *game,
				t_vec2 ray_dir, size_t hit_side)
{
	if (hit_side == 0 && ray_dir.x < 0)
		return (&game->sprites.west);
	else if (hit_side == 0 && ray_dir.x > 0)
		return (&game->sprites.east);
	else if (hit_side == 1 && ray_dir.y < 0)
		return (&game->sprites.north);
	else
		return (&game->sprites.south);
}

#endif
