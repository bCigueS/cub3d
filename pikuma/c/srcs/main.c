/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:07:59 by sbeylot           #+#    #+#             */
/*   Updated: 2022/12/16 16:51:43 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_map(t_cub3d *cub);
bool init_cub(t_cub3d	*cub) 
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->img.img = NULL;
	cub->player = NULL;
	cub->mlx_ptr = mlx_init();		
	if (cub->mlx_ptr == NULL)
		return (false);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (cub->win_ptr == NULL)
		return (false);
	cub->img.img = mlx_new_image(cub->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (cub->img.img == NULL)
		return (false);
	cub->img.addr = (int *)mlx_get_data_addr(cub->img.img, \
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	if (cub->img.addr == NULL)
		return (false);
	return (true);
}

void	clean_cub(t_cub3d *cub) 
{
	if (cub->img.img != NULL)
		mlx_destroy_image(cub->mlx_ptr, cub->img.img);
	if (cub->win_ptr != NULL)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->mlx_ptr != NULL)
		mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
}

int	cub_error(void)
{
	ft_putstr_fd("Error in Mlx initialisation", 2);
	return (MLX_ERROR);
}

int	quit(t_cub3d *cub)
{
	mlx_loop_end(cub->mlx_ptr);
	exit(0);
	return (0);
}

int	handle_key(int keycode, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(cub->mlx_ptr);
		cub->loop = 0;
	}
	if (keycode == KEY_W) {
		cub->player->y -= 1 * cub->player->mspeed;
		render_map(cub); 
	}
	if (keycode == KEY_S) {
		cub->player->y += 1 *cub->player->mspeed;
		render_map(cub);
	}
	if (keycode == KEY_A) {
		cub->player->x -= 1 *cub->player->mspeed;
		render_map(cub);
	}
	if (keycode == KEY_D) {
		cub->player->x += 1 *cub->player->mspeed;
		render_map(cub);
	}
	return (0);
}

void	render_map(t_cub3d *cub)
{
	draw_background(cub);
	draw_wall(cub);
	draw_grid(cub);
	draw_player(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img, 0, 0);
}

int	cub3d(t_cub3d *cub) 
{
	if (init_cub(cub) == false)
		return (clean_cub(cub), cub_error());
	if (init_player(cub) == false)
		return (clean_cub(cub), cub_error());
	mlx_hook(cub->win_ptr, KEY_PRESS, (1L<<0) , &handle_key, cub);
	mlx_hook(cub->win_ptr, EXIT, 0, &quit, cub);
	while (cub->loop == 1)
	{
		time_t	start_time = time(NULL);
		render_map(cub);
		mlx_loop(cub->mlx_ptr);
		time_t	elapsed_time = time(NULL) - start_time;
		int sleep_time_ms = FPMS - elapsed_time * 1000;
		if (sleep_time_ms > 0)
			usleep(sleep_time_ms * 1000);
	}
	clean_cub(cub);
	return (0);
}

int	**init_map(int map[MH][MW])
{
	int	i;
	int	**pmap;

	(void)map;

	i = 0;
	pmap = (int **)malloc(sizeof(int *) * MH);
	if (!pmap)
		return (NULL);
	while (i < MH)
	{
		pmap[i] = ft_calloc(MW, sizeof(int));
		if (!pmap[i])
			return (NULL); // Add un clean
		i++;
	}
	pmap[5][5] = 'P';
	return (pmap);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int map[MH][MW] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	t_cub3d	cub;
	cub.loop = 1;
	cub.map = init_map(map);
	cub3d(&cub);	
	return (0);
}
