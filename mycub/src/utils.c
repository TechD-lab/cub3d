/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:01:15 by jinspark          #+#    #+#             */
/*   Updated: 2021/05/07 12:01:17 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	normalize_angle(float angle)
{
	angle = remainderf(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float	points_dist(float x1, float x2, float y1, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int		is_wall(int x, int y, t_map *map)
{
	int	row;
	int	col;

	if (x < 0 || x >= TILE_SIZE * map->width ||
			y < 0 || y >= TILE_SIZE * map->height)
		return (TRUE);
	row = y / TILE_SIZE;
	col = x / TILE_SIZE;
	return (map->grid[row][col] == 1);
}
