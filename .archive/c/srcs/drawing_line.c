/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:06:53 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/16 14:31:40 by sbeylot          ###   ########.fr       */
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

void	draw_line(t_cub3d *cub, t_line line)
{
	int err2;
	while (1)
	{
		draw_pixel(cub, init_pixel(line.x, line.y, line.color));
		if (line.x == line.p2.x && line.y == line.p2.y)
			break;
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

/*
 * GPT
 Certainly! Here is a step-by-step explanation of what the draw_line function
 does:

The function starts by calculating the differences between the x and y 
coordinates of the two points that define the line. These differences are used 
to determine the direction and slope of the line.

The function then determines the direction of the line by checking the sign of 
the x and y differences. If the x difference is positive, the line is drawn 
from left to right and the sx variable is set to 1. If the x difference is 
negative, the line is drawn from right to left and sx is set to -1. Similarly, 
if the y difference is positive, the line is drawn from top to bottom and sy 
is set to 1, otherwise sy is set to -1.

The function initializes the error term, which is used to adjust the position 
of the line as it is drawn. This error term is initialized to the difference 
between the x and y differences, which represents the initial error between 
the line and the grid.

The function then enters a loop that iterates over the points on the line. 
Inside the loop, the function sets the pixel at the current position of the 
line using the set_pixel function.

The function then checks if the current position of the line is the same as the 
final position of the line. If it is, the function breaks out of the loop and 
returns.

If the current position is not the final position, the function updates the 
error term by adding the differences between the x and y differences. If the 
error term exceeds a certain threshold, the position of the line is adjusted 
by adding or subtracting the sx or sy value. This helps to keep the line as 
close as possible to the true mathematical line as it is drawn.

The loop then repeats, updating the position of the line and the error term 
until the final position is reached.

I hope this helps to clarify how the draw_line function works! Let me know if 
you have any further questions.
*/
