/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:55:53 by jinspark          #+#    #+#             */
/*   Updated: 2021/05/03 15:12:59 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_hud(t_mlx *mlx, t_pars *par, t_info *info)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;
	
	resize_h = (par->reso[1] / (double)info->hud[HEIGHT]) * (HUD_SIZE_H);
	resize_w = (par->reso[0] / (double)info->hud[WIDTH]);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < info->hud[HEIGHT])
	{
		row = 0.0;
		while ((int)(row / resize_w) < info->hud[WIDTH])
		{
			mlx->addr.screen[(int)row + (int)(mlx->par->reso[1] * (1.0 - HUD_SIZE_H)) *
					info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
					= mlx->addr.hud[(int)(row / resize_w) + (int)(line / resize_h)
					* info->hud[SIZE_LINE]];
			row += 1.0;
		}
		line += 1.0;
	}
}

int		lifebar_color(t_mlx *mlx, t_info *info, int row, int line)
{
	int		color;

	if (((double)row / (double)LIFE_PIX_W) < ((double)mlx->eve.lifebar / (double)FULL_LIFE))
		color = mlx->addr.life[row + LIFE_RED_IMG_R + line * info->life[SIZE_LINE]
				+ LIFE_RED_IMG_L * info->life[SIZE_LINE]];
	else
		color = mlx->addr.life[row + LIFE_EMPTY_IMG_R + line * info->life[SIZE_LINE]
				+ LIFE_EMPTY_IMG_L * info->life[SIZE_LINE]];
	return (color);
}

void	draw_lifebar(t_mlx *mlx, t_pars *par, t_info *info)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;

	resize_h = (par->reso[1] / (double)LIFE_PIX_H) * (LIFE_SIZE_H);
	resize_w = (par->reso[0] / (double)LIFE_PIX_W) * (LIFE_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < LIFE_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < LIFE_PIX_W)
		{
			if (lifebar_color(mlx, info, (int)(row / resize_w), (int)(line / resize_h)) != INV_COLOR)
				mlx->addr.screen[(int)row + (int)(LIFE_SCREEN_R * mlx->par->reso[0]) + (int)(mlx->par->reso[1]
						* LIFE_SCREEN_L) * info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
						= lifebar_color(mlx, info, (int)(row / resize_w), (int)(line / resize_h));
			row += 1.0;
		}
		line += 1.0;
	}
}

int		gun_color(t_mlx *mlx, int num_sprite, int row, int line)
{
	int		color;
	
	color = mlx->addr.guns[row + GUNS_IMG_R * num_sprite + line * mlx->info.guns[SIZE_LINE]
			+ GUNS_IMG_L * mlx->info.guns[SIZE_LINE]];
	return (color);
}

void	draw_gun(t_mlx *mlx, t_pars *par, t_info *info, int num_sprite)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;

	resize_h = (par->reso[1] / (double)GUNS_PIX_H) * (GUNS_SIZE_H);
	resize_w = (par->reso[0] / (double)GUNS_PIX_W) * (GUNS_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < GUNS_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < GUNS_PIX_W)
		{
			if (gun_color(mlx, num_sprite, (int)(row / resize_w), (int)(line / resize_h)) != INV_COLOR)
				mlx->addr.screen[(int)row + (int)(GUNS_SCREEN_R * mlx->par->reso[0]) + (int)(mlx->par->reso[1]
						* GUNS_SCREEN_L) * info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
						= gun_color(mlx, num_sprite, (int)(row / resize_w), (int)(line / resize_h));
			row += 1.0;
		}
		line += 1.0;
	}
}