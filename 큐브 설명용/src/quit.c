/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:00:32 by jinspark          #+#    #+#             */
/*   Updated: 2021/05/19 23:52:33 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
/*
t_cub 안에 메모리 모두 프리 해주는 함수
이미지는 mlx_destroy_image, 윈도우는 mlx_destroy_window 로 프리.
*/
void	quit_cub(t_cub *cub, int exit_code, char *error_message)
{
	int	i;

	free(cub->rays);
	free(cub->sprites);
	ft_free_int_matrix(cub->map.grid, cub->map.height);
	i = 0;
	while (i < TEXTURES)
	{
		free(cub->map.paths[i]);
		if (cub->texture[i].image.img)
			mlx_destroy_image(cub->mlx, cub->texture[i].image.img);
		i++;
	}
	if (cub->mlx && cub->image.img)
		mlx_destroy_image(cub->mlx, cub->image.img);
	if (cub->mlx && cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
	ft_bzero(cub, sizeof(t_cub));
	if (exit_code == EXIT_FAILURE)
		ft_putendl_fd(error_message, 2);
	exit(exit_code);
}
