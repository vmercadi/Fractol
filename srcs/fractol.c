/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:38:11 by vmercadi          #+#    #+#             */
/*   Updated: 2017/10/05 15:54:49 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Clear the current image, draw the new one and display it
*/

void	refresh(t_base *base)
{
	mthread(base);
	mlx_put_image_to_window(base->mx.mlx, base->mx.win, base->mx.img, 0, 0);
	ui(base);
}

/*
** Call the fractal given in arg
*/

void	fractol(t_base *base)
{
	refresh(base);
	mlx_hook(base->mx.win, 2, 0, event, base);
	mlx_hook(base->mx.win, 6, 0, evmv_mouse, base);
	mlx_hook(base->mx.win, 17, 0, clean, base);
	mlx_mouse_hook(base->mx.win, ev_mouse, base);
	mlx_loop(base->mx.mlx);
}

int		main(int ac, char **av)
{
	t_base base;

	if (ac != 2)
		error(1);
	if (!ft_strcmp(av[1], "usage"))
		error(0);
	init_base(&base, av[1]);
	fractol(&base);
	return (0);
}
