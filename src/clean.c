/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:25:04 by gwenolalero       #+#    #+#             */
/*   Updated: 2023/04/07 11:19:43 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_error(char *err_msg, int fd)
{
	if (err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	if (fd)
		close (fd);
	exit(EXIT_FAILURE);
}

void	ft_clean_up(t_fdf *ms, char *err_msg)
{
	if (ms->mlx)
		mlx_terminate(ms->mlx);
	if (ms->infos && ms->infos->matrix)
	{
		ft_free_tab_int(ms->infos->matrix, (size_t)ms->infos->height);
		free(ms->infos);
	}
	free(ms);
	if (err_msg)
		ft_error(err_msg, 2);
}
