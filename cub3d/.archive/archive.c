bool	update_ray2(t_cub3d *cub)
{
	t_player 	*p;
	t_ray		*r;
	int			xstep;
	int			ystep;
	int			xintercept;
	int			yintercept;

	p = cub->player;
	r = cub->ray;
	yintercept = floor(p->y / TILE_SIZE) * TILE_SIZE;
	if (r->ray_down)
		yintercept += TILE_SIZE;
	xintercept = p->x + (yintercept - p->y) / tan(r->rangle);
	ystep = TILE_SIZE;
	if (!r->ray_down)
		ystep *= -1;
	xstep = TILE_SIZE / tan(r->rangle);
	if (r->ray_left && xstep > 0)
		xstep *= -1;
	if (!r->ray_left && xstep < 0)
		xstep *= -1;

	int	nextx = xintercept;
	int	nexty = yintercept;

	if (!r->ray_down)
		nexty--;
	while (nextx >= 0 && nextx <= WINDOW_WIDTH && nexty >= 0 && nexty <= WINDOW_HEIGHT)
	{
		if (is_a_wall(cub, nextx, nexty)) {
			if (!r->ray_down)
				nexty++;
			r->xwallh = nextx;
			r->ywallh = nexty;
			return (true);
		}
		else {
			nextx += xstep;
			nexty += ystep;
		}
	}
	return (false);
}

bool	update_ray3(t_cub3d *cub)
{
	t_player 	*p;
	t_ray		*r;
	int			xstep;
	int			ystep;
	int			xintercept;
	int			yintercept;

	p = cub->player;
	r = cub->ray;
	xintercept = floor(p->x / TILE_SIZE) * TILE_SIZE;
	if (!r->ray_left)
		xintercept += TILE_SIZE;
	yintercept = p->y + (xintercept - p->x) * tan(r->rangle);
	xstep = TILE_SIZE;
	if (r->ray_left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(r->rangle);
	if (!r->ray_down && ystep > 0)
		ystep *= -1;
	if (r->ray_down && ystep < 0)
		ystep *= -1;

	int	nextx = xintercept;
	int	nexty = yintercept;

	if (r->ray_left)
		nextx--;
	while (nextx >= 0 && nextx <= WINDOW_WIDTH && nexty >= 0 && nexty <= WINDOW_HEIGHT)
	{
		if (is_a_wall(cub, nextx, nexty)) {
			nextx--;
			//draw_line(cub, init_line(init_pixel(p->x, p->y, RED), init_pixel(nextx, nexty, RED)));
			r->xwallv = nextx;
			r->ywallv = nexty;
			return (true);
		}
		else {
			nextx += xstep;
			nexty += ystep;
		}
	}
	return (false);
}
