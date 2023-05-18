/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:21:59 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 20:37:30 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdio.h>
# include <math.h>
# include "cub3d.h"

typedef struct
{
	double	x;
	double	y;
}	t_vec2;

typedef struct
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw;

inline static t_vec2	vec_add(t_vec2 lhs, t_vec2 rhs)
{
	return (t_vec2){lhs.x + rhs.x, lhs.y + rhs.y};
}

inline static t_vec2	vec_mul(t_vec2 lhs, t_vec2 rhs)
{
	return (t_vec2){lhs.x * rhs.x, lhs.y * rhs.y};
}

void	start(t_game *game);

#endif
