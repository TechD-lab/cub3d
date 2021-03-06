/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinspark <jinspark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:01:01 by jinspark          #+#    #+#             */
/*   Updated: 2021/05/19 15:15:09 by jinspark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	initialize_bit_file_header(t_bitmap_file_header *bfh, t_cub *cub)
{
	bfh->bf_reverved1 = 0;
	bfh->bf_reserved2 = 0;
	bfh->bf_off_bits = 54;
	bfh->bf_size = 2 + sizeof(t_bitmap_file_header) +
					sizeof(t_bitmap_info_header) +
					cub->width * cub->height * 4;
}

static void	initialize_bit_info_header(t_bitmap_info_header *bih, t_cub *cub)
{
	bih->bi_size = sizeof(t_bitmap_info_header);
	bih->bi_width = cub->width;
	bih->bi_height = cub->height;
	bih->bi_planes = 1;
	bih->bi_bit_count = 32;
	bih->bi_compression = 0;
	bih->bi_size_image = 0;
	bih->bi_x_pels_per_meter = 2850;
	bih->bi_y_pels_per_meter = 2850;
	bih->bi_clr_used = 0;
	bih->bi_clr_important = 0;
}

static void	write_bitmap_to_image(t_bitmap_file_header *bfh,
		t_bitmap_info_header *bih, int fd, t_cub *cub)
{
	unsigned short	bf_type;
	int				y;
	int				x;
	int				pixel;

	bf_type = 0x4d42;
	if ((write(fd, &bf_type, sizeof(bf_type))) < 0)
		quit_cub(cub, EXIT_FAILURE, ERR_WR);
	if ((write(fd, bfh, sizeof(*bfh))) < 0)
		quit_cub(cub, EXIT_FAILURE, ERR_WR);
	if ((write(fd, bih, sizeof(*bih))) < 0)
		quit_cub(cub, EXIT_FAILURE, ERR_WR);
	y = bih->bi_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < bih->bi_width)
		{
			pixel = pixel_get(&cub->image, x, y);
			if ((write(fd, &pixel, sizeof(pixel))) < 0)
				quit_cub(cub, EXIT_FAILURE, ERR_WR);
			x++;
		}
		y--;
	}
}

void		save_bitmap(t_cub *cub)
{
	t_bitmap_file_header	bfh;
	t_bitmap_info_header	bih;
	int						fd;

	initialize_bit_file_header(&bfh, cub);
	initialize_bit_info_header(&bih, cub);
	fd = open(SCREENSHOT, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		quit_cub(cub, EXIT_FAILURE, "Open error.");
	write_bitmap_to_image(&bfh, &bih, fd, cub);
	close(fd);
}
