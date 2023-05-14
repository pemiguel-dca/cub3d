/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:30:08 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/14 16:26:57 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_H
# define VALIDATE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft/libft.h"

typedef struct
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_validate;

static inline bool validate_types(char **identifiers)
{
	t_validate	val;
	size_t		i;

	i = 0;
	val = (t_validate){.no = 0, .so = 0, .we = 0, .ea = 0, .f = 0, .c = 0};
	while (identifiers[i])
	{
		if (ft_strcmp(identifiers[i], "NO") == 0 || (ft_strcmp(identifiers[i], "N") == 0 && ft_strlen(identifiers[i]) == 1))
			val.no += 1;
		else if (ft_strcmp(identifiers[i], "SO") == 0 || (ft_strcmp(identifiers[i], "S") == 0 && ft_strlen(identifiers[i]) == 1))
			val.so += 1;
		else if (ft_strcmp(identifiers[i], "WE") == 0 || (ft_strcmp(identifiers[i], "W") == 0 && ft_strlen(identifiers[i]) == 1))
			val.we += 1;
		else if (ft_strcmp(identifiers[i], "EA") == 0 || (ft_strcmp(identifiers[i], "E") == 0 && ft_strlen(identifiers[i]) == 1))
			val.ea += 1;
		else if (ft_strcmp(identifiers[i], "F") == 0)
			val.f += 1;
		else if (ft_strcmp(identifiers[i], "C") == 0)
			val.c += 1;
		i += 1;
	}
	return (val.no == 1 && val.so == 1 && val.we == 1
			&& val.ea == 1 && val.f == 1 && val.c == 1);
}

#endif
