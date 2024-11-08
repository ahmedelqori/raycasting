/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:53:38 by ael-qori          #+#    #+#             */
/*   Updated: 2024/10/24 13:11:45 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub_bonus.h"

void		get_textures_x(t_container *container);
int			img_px(t_texturedata img, int x, int y);
static int	draw_doors(t_container *container, int x, int y);
void		draw_pixels_to_screen(t_container *container, int x, int y);

void	draw_images_to_game(t_container *container, int x)
{
	int		y;
	double	step;
	int		tex_height;

	tex_height = container->bundles.walls.orientations[0].height;
	y = container->bundles.walls.drawstart;
	get_textures_x(container);
	step = 1.0 * tex_height / container->bundles.walls.lineheight;
	container->bundles.walls.texy = (container->bundles.walls.drawstart
			- SCREEN_HEIGHT / 2 + \
			container->bundles.walls.lineheight / 2) * step;
	while (y < container->bundles.walls.drawend)
	{
		container->bundles.walls.texy += step;
		draw_pixels_to_screen(container, x, y);
		y++;
	}
	container->player.hit = 0;
}

void	get_textures_x(t_container *container)
{
	int	tex_width;

	tex_width = container->bundles.walls.orientations[0].width;
	if (container->player.side == 0)
		container->bundles.walls.wallx = container->player.pos.vert
			+ container->player.perpwalldist * container->player.ray.vert;
	else
		container->bundles.walls.wallx = container->player.pos.horz
			+ container->player.perpwalldist * container->player.ray.horz;
	container->bundles.walls.wallx -= floor(container->bundles.walls.wallx);
	container->bundles.walls.texx = (int)(container->bundles.walls.wallx
			* (double)tex_width);
	if (container->player.side == 1 && container->player.ray.vert > 0)
		container->bundles.walls.texx = tex_width - \
		container->bundles.walls.texx - 1;
	if (container->player.side == 0 && container->player.ray.horz < 0)
		container->bundles.walls.texx = tex_width - \
		container->bundles.walls.texx - 1;
}

int	img_px(t_texturedata img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length)
			+ (x * img.bits_per_pixel / 8))));
}

void	draw_pixels_to_screen(t_container *container, int x, int y)
{
	if (draw_doors(container, x, y))
		;
	else if (container->player.side == 0 && container->player.ray.horz > 0)
		paint_on_screen_by_pixel(&container->bundles.background, x, y,
			img_px(container->bundles.walls.orientations[2],
				container->bundles.walls.texx, container->bundles.walls.texy));
	else if (container->player.side == 0 && container->player.ray.horz < 0)
		paint_on_screen_by_pixel(&container->bundles.background, x, y,
			img_px(container->bundles.walls.orientations[3],
				container->bundles.walls.texx, container->bundles.walls.texy));
	else if (container->player.side == 1 && container->player.ray.vert < 0)
		paint_on_screen_by_pixel(&container->bundles.background, x, y,
			img_px(container->bundles.walls.orientations[0],
				container->bundles.walls.texx, container->bundles.walls.texy));
	else if (container->player.side == 1 && container->player.ray.vert > 0)
		paint_on_screen_by_pixel(&container->bundles.background, x, y,
			img_px(container->bundles.walls.orientations[1],
				container->bundles.walls.texx, container->bundles.walls.texy));
	if (x == SCREEN_WIDTH / 2 && y == SCREEN_HEIGHT / 2)
		paint_on_screen_by_pixel(&container->bundles.background \
			, x, y, 0xFFFFFF);
}

static int	draw_doors(t_container *container, int x, int y)
{
	int	px;

	if (container->player.hit == 3)
		paint_on_screen_by_pixel(&container->bundles.background, x, y,
			img_px(container->bundles.walls.door[0],
				container->bundles.walls.texx, container->bundles.walls.texy));
	else if (container->player.hit == 4)
	{
		px = img_px(container->bundles.walls.door[1],
				container->bundles.walls.texx, container->bundles.walls.texy);
		if (px != (int)0xFF000000)
			paint_on_screen_by_pixel(&container->bundles.background, x, y, px);
		else
			paint_on_screen_by_pixel(&container->bundles.background \
				, x, y, 0x000000);
	}
	else
		return (FALSE);
	return (TRUE);
}
