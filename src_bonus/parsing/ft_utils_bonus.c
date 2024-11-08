/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relhamma <relhamma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:01:18 by relhamma          #+#    #+#             */
/*   Updated: 2024/10/23 15:27:43 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub_bonus.h"

int	is_wall(char c)
{
	if (c == '1')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_orientation(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_empty_space(char c)
{
	if (c == '0')
		return (1);
	return (0);
}

int	ft_check_entity(char c)
{
	if (!is_empty_space(c) && !is_orientation(c) && !is_space(c) && !is_wall(c)
		&& !is_door(c))
		return (0);
	return (1);
}
