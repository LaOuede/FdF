/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:15:28 by gwenolalero       #+#    #+#             */
/*   Updated: 2023/04/18 13:02:09 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* Initialize and set the graphic library and the window */
bool	ft_init_mlx(t_fdf *ms, char *file)
{
	ms->mlx = mlx_init(WIDTH, HEIGHT, file, false);
	ms->image = mlx_new_image(ms->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(ms->mlx, ms->image, 0, 0);
	if (!ms->mlx || !ms->image
		|| (mlx_image_to_window(ms->mlx, ms->image, 0, 0) == 0))
		ft_clean_up(ms, KRED"MLX initialization failed\n"KNRM);
	return (T);
}

int	main(int argc, char **argv)
{
	t_fdf	*ms;

	if (argc != 2)
		ft_clean_up(0, "Usage : ./fdf <map.fdf>\n"
			KYEL"	-> An argument is needed <-\n"KNRM);
	ms = ft_init_ms();
	ft_parse_file(ms, argv[1]);
	ft_read_map(ms, argv[1]);
	if (ft_init_mlx(ms, argv[1]) == T)
	{
		mlx_key_hook(ms->mlx, &ft_fdf_keys, ms);
		ft_draw(ms);
		ft_add_menu(ms);
		mlx_loop(ms->mlx);
	}
	ft_clean_up(ms, 0);
	exit(EXIT_SUCCESS);
}
