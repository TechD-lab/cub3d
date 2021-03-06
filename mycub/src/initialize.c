/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:59:41 by jinspark          #+#    #+#             */
/*   Updated: 2021/05/07 11:59:42 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void		initialize_player_sprites(t_player *player, t_cub *cub)
{
	int	i;

	player->turn_direction = 0;
	player->walk_direction = 0;
	player->strafe_direction = 0;
	player->walk_speed = WALK_SPEED;
	player->turn_speed = TURN_SPEED * (PI / 180);
	cub->map.player.x = cub->map.player.map_x * TILE_SIZE + TILE_SIZE / 2;
	cub->map.player.y = cub->map.player.map_y * TILE_SIZE + TILE_SIZE / 2;
	i = 0;
	while (i < cub->map.sprites)
	{
		cub->sprites[i].x = cub->sprites[i].map_x * TILE_SIZE + TILE_SIZE / 2;
		cub->sprites[i].y = cub->sprites[i].map_y * TILE_SIZE + TILE_SIZE / 2;
		i++;
	}
}

static void		load_texture(t_cub *cub, t_texture *texture, char *path)
{
	texture->image.img = mlx_xpm_file_to_image(cub->mlx, path,
			&texture->width, &texture->height);
	if (!texture->image.img)
		quit_cub(cub, EXIT_FAILURE, "Invalid texture.");
	texture->image.addr = mlx_get_data_addr(
			texture->image.img,
			&texture->image.bits_per_pixel,
			&texture->image.size_line,
			&texture->image.endian);
}

static void		initialize_image(t_cub *cub)
{
	cub->image.img = mlx_new_image(cub->mlx, cub->width,
			cub->height);
	if (!cub->image.img)
		quit_cub(cub, EXIT_FAILURE, "Image error.");
	cub->image.addr = mlx_get_data_addr(
			cub->image.img,
			&cub->image.bits_per_pixel,
			&cub->image.size_line,
			&cub->image.endian);
	load_texture(cub, &cub->texture[EAST], cub->map.paths[EAST]);
	load_texture(cub, &cub->texture[WEST], cub->map.paths[WEST]);
	load_texture(cub, &cub->texture[SOUTH], cub->map.paths[SOUTH]);
	load_texture(cub, &cub->texture[NORTH], cub->map.paths[NORTH]);
	load_texture(cub, &cub->texture[SPRITE], cub->map.paths[SPRITE]);
	if (cub->savebmp == 0)
	{
		cub->win = mlx_new_window(cub->mlx, cub->width, cub->height, TITLE);
		if (!cub->win)
			quit_cub(cub, EXIT_FAILURE, "Can't create a new window.");
	}
}

static void		initialize_cub(t_cub *cub)
{
	int	width;
	int	height;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		quit_cub(cub, EXIT_FAILURE, "Can't connect to the X server.");
	mlx_get_screen_size(cub->mlx, &width, &height);
	cub->width = ft_min(cub->width, width);
	cub->height = ft_min(cub->height, height);
	cub->rays = malloc(sizeof(t_ray) * cub->width);
	if (cub->rays == NULL)
		quit_cub(cub, EXIT_FAILURE, ERR_MEM);
	cub->fov_angle = FOV * (PI / 180);
	cub->half_fov_angle = (FOV / 2) * (PI / 180);
	cub->angle_step = cub->fov_angle / cub->width;
	cub->dist_proj_plane = (cub->width / 2) / tan(cub->half_fov_angle);
}

void			initialize(t_cub *cub)
{
	initialize_cub(cub);
	initialize_player_sprites(&cub->map.player, cub);
	initialize_image(cub);
}
