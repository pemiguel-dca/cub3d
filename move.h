/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:46:31 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 13:00:34 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include "cub3d.h"

# define MOVE_SPEED 0.07

void	move_foward(t_game *game);
void	move_backwards(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

#endif
