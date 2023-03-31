/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:15:28 by gwenolalero       #+#    #+#             */
/*   Updated: 2023/03/31 13:10:37 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	static t_map_infos	map = {0, 0, 0, 0, false};

	(void) map;
	if (argc != 2)
		ft_error_args("Usage : ./fdf <map.fdf>\n"
			KYEL"	-> 1 argument is needed\n"KNRM);
	ft_parse_file(argv[1]);
	//ft_parse_map(&map, argv[1]);
	return (0);
}
