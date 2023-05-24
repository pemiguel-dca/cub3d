/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:49:16 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 13:01:31 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATE_H
# define ROTATE_H

# define ROTATION_SPEED 0.1

# include "cub3d.h"
# include <math.h>

void	rotate_left(t_game *game, t_vec2 old_player_dir,
			t_vec2 old_camera_plane);
void	rotate_right(t_game *game, t_vec2 old_player_dir,
			t_vec2 old_camera_plane);

#endif
