/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:34:37 by gwenolalero       #+#    #+#             */
/*   Updated: 2023/04/12 18:18:10 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* void	ft_find_scale(t_fdf *ms)
{
	while (42)
	{
		if (ft_limits(ms) == T)
			ms->map->scale += 5;
	}
	ft_printf("   -> scale  ="KYEL"  %d\n"KNRM, ms->map->scale);
}
 */

/* Get the starting points on the screen */
void	ft_get_starting_points(t_fdf *ms)
{
	ms->map->x_start = (WIDTH / 2) - (ms->map->width * ms->cam->scale / 2);
	printf("x_start = %f\n", ms->map->x_start);
	ms->map->y_start = (HEIGHT / 2) - (ms->map->height * ms->cam->scale / 2);
	printf("y_start = %f\n", ms->map->y_start);
	printf("height = %f\n", ms->map->height);
	printf("scale = %d\n", ms->cam->scale);
}

/* Draw the points of the map */
/* void	ft_draw_map_square(t_fdf *ms)
{
	double	x;
	double	y;

	x = ms->map->x_start;
	while (x < (ms->map->x_start + ms->map->width * ms->cam->scale))
	{
		y = ms->map->y_start;
		while (y < (ms->map->y_start + ms->map->height * ms->cam->scale))
		{
			mlx_put_pixel(ms->image, (x + ms->cam->x_offset), (y + ms->cam->y_offset), 0xffffff);
			y += ms->cam->scale;
		}
		x += ms->cam->scale;
	}
} */

void	ft_draw_map_square(t_fdf *ms)
{
	int	x;
	int	y;
	int	a;
	int	o;

	y = ms->map->y_start;
	o = 0;
	ft_map_erase(ms);
	while (y < (ms->map->y_start + ms->map->height * ms->cam->scale))
	{
		x = ms->map->x_start;
		a = 0;
		while (x < (ms->map->x_start + ms->map->width * ms->cam->scale))
		{
			if (x < (ms->map->x_start + ms->map->width * ms->cam->scale) - ms->cam->scale)
			{
				ms->coord->start_x = x;
				ms->coord->start_y = y;
				ms->coord->start_z = ms->map->matrix[o][a];
				ms->coord->end_x = x + ms->cam->scale;
				ms->coord->end_y = y;
				ms->coord->end_z = ms->map->matrix[o][a + 1];
				ft_draw_line(ms);
			}
			if (y < (ms->map->y_start + ms->map->height * ms->cam->scale) - ms->cam->scale)
			{
				ms->coord->start_x = x;
				ms->coord->start_y = y;
				ms->coord->start_z = ms->map->matrix[o][a];
				ms->coord->end_x = x;
				ms->coord->end_y = y + ms->cam->scale;
				ms->coord->end_z = ms->map->matrix[o + 1][a];
				ft_draw_line(ms);
			}
			x += ms->cam->scale;
			a++;
		}
		y += ms->cam->scale;
		o++;
	}
}

/* void	ft_draw_line(t_fdf *ms, t_point start, t_point end)
{
	int	x;
	int	y;

	ms->algo->delta_x = fabs(end.x - start.x);
	ms->algo->delta_y = fabs(end.y - start.y);
	ms->algo->ptp = (2 * ms->algo->delta_y) - ms->algo->delta_x;
	x = start.x;
	y = start.y;
	while(x < end.x)
	{
		if (ms->algo->ptp >= 0)
		{
			mlx_put_pixel(ms->image, (x + ms->cam->x_offset), (y + ms->cam->y_offset), 0xffffff);
			y += 1;
			ms->algo->ptp = ms->algo->ptp + 2 * ms->algo->delta_y - 2 * ms->algo->delta_x;
		}
		else
		{
			mlx_put_pixel(ms->image, (x + ms->cam->x_offset), (y + ms->cam->y_offset), 0xffffff);
			ms->algo->ptp = ms->algo->ptp + 2 * ms->algo->delta_y;
		}
		x += 1;
	}
} */

void	ft_draw_line(t_fdf *ms)
{
	int	pixel;

	ms->algo->delta_x = fabs(ms->coord->end_x - ms->coord->start_x);
	ms->algo->delta_y = fabs(ms->coord->end_y - ms->coord->start_y);
	ms->algo->delta_max = (int)fmax(ms->algo->delta_x, ms->algo->delta_y);
	ms->algo->delta_x /= ms->algo->delta_max;
	ms->algo->delta_y /= ms->algo->delta_max;
	pixel = -1;
	while (++pixel <= ms->algo->delta_max)
	{
		if (ms->coord->start_x >= 0 && ms->coord->start_y >= 0
			&& ms->coord->start_x < WIDTH && ms->coord->start_y < HEIGHT)
		{
			if ((int)ms->coord->start_z < 0)
				mlx_put_pixel(ms->image, (ms->coord->start_x + \
					ms->cam->x_offset), (ms->coord->start_y + \
					ms->cam->y_offset), 0x34ebeb);
			else if ((int)ms->coord->start_z == 0)
				mlx_put_pixel(ms->image, (ms->coord->start_x + \
					ms->cam->x_offset), (ms->coord->start_y + \
					ms->cam->y_offset), 0xebdf34);
			else if ((int)ms->coord->start_z > 0)
				mlx_put_pixel(ms->image, (ms->coord->start_x + \
					ms->cam->x_offset), (ms->coord->start_y + \
					ms->cam->y_offset), 0xffffff);
		}
		ms->coord->start_x += ms->algo->delta_x;
		ms->coord->start_y += ms->algo->delta_y;
	}
}



/* Draw the points of the previous image with the background color */
void	ft_map_erase(t_fdf *ms)
{
	double	x;
	double	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(ms->image, x, y, 0x000000);
			y++;
		}
		x++;
	}
}
