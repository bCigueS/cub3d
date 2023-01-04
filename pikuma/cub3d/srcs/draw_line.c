/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:11:51 by sbeylot           #+#    #+#             */
/*   Updated: 2023/01/04 15:48:46 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pixel	init_pixel(int x, int y, int color)
{
	t_pixel	p;

	p.x = x;
	p.y = y;
	p.color = color;
	return (p);
}

t_line	init_line(t_pixel p1, t_pixel p2)
{
	t_line	line;

	line.p1 = p1;
	line.p2 = p2;
	line.x = line.p1.x;
	line.y = line.p1.y;
	line.dx = line.p2.x - line.p1.x;
	line.dy = line.p2.y - line.p1.y;
	line.xstep = 1;
	if (line.dx < 0)
	{
		line.xstep = -1;
		line.dx = -line.dx;
	}
	line.ystep = 1;
	if (line.dy < 0)
	{
		line.ystep = -1;
		line.dy = -line.dy;
	}
	line.err = line.dx - line.dy;
	line.color = p1.color;
	return (line);
}

void	draw_line(t_img img, t_line line)
{
	int	err2;

	while (1)
	{
		draw_pixel(img, init_pixel(line.x, line.y, line.color));
		if (line.x == line.p2.x && line.y == line.p2.y)
			break ;
		err2 = 2 * line.err;
		if (err2 > -line.dy)
		{
			line.err = line.err - line.dy;
			line.x = line.x + line.xstep;
		}
		if (err2 < line.dx)
		{
			line.err = line.err + line.dx;
			line.y = line.y + line.ystep;
		}
	}
}