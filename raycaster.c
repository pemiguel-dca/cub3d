/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:37 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 12:35:18 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

t_raycaster	*init_rc(const char **buffer)
{
	t_raycaster	*rc;

	rc = malloc(sizeof(t_raycaster));
	rc->player_pos = player_pos(buffer);

	return (rc);
}
