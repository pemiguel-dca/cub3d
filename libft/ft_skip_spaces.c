/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:19:44 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 16:20:48 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_skip_spaces(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i += 1;
	return (i);
}
