static void	choose_color(t_ray *r, t_pixel *start, t_pixel *end)
{
	unsigned int color;
	if (r->is_horizontal_hit && r->ray_down)
		color = RED;
	else if (r->is_horizontal_hit && !r->ray_down)
		color = GREEN;
	else if (!r->is_horizontal_hit && r->ray_left)
		color = BLUE;
	else if (!r->is_horizontal_hit && !r->ray_left)
		color = GOLD;
	else 
		color = BLACK;
	start->color = color;
	end->color = color;
}
static void	raycasting_draw_wall(t_cub3d *cub, t_rcinfo rci, t_ray *r, int *pi)
{
	int		next;
	t_pixel	start;
	t_pixel	end;
	next = *pi + STRIP;
	choose_color(r, &start, &end);
	while (*pi < next)
	{
		start = init_pixel(*pi, WINDOW_HEIGHT / 2 - (rci.wall_height / 2), \
				start.color);
		end = init_pixel(*pi, WINDOW_HEIGHT / 2 + (rci.wall_height / 2), \
				end.color);
		draw_line(cub->img, init_line(start, end));
		*pi += 1;
	}
}
*/
