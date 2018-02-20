/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:32:42 by vmercadi          #+#    #+#             */
/*   Updated: 2018/02/20 15:29:57 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_base(t_base *base, char *av)
{
	base->av = ft_strdup(av);
	base->winx = WINX;
	base->winy = WINY;
	base->mx.bpp = 8;
	base->mx.endian = 0;
	base->win_size = base->winx * base->winy;
	base->mouse = 1;
	base->ui1 = 0;
	base->ui2 = 0;
	base->ui3 = 0;
	base->mx.sizeline = base->winy;
	base->frfr = init_fract(base);
	base->j = get_fractal(av);
	base->hide = 0;
	base->autoiter = 0;
	base->mx.mlx = mlx_init();
	base->mx.win = mlx_new_window(
		base->mx.mlx, base->winx, base->winy, "Fractol");
	base->mx.img = mlx_new_image(base->mx.mlx, base->winx, base->winy);
	base->mx.data = (int*)mlx_get_data_addr(
		base->mx.img, &base->mx.bpp, &base->mx.sizeline, &base->mx.endian);
	mlx_string_put(base->mx.mlx, base->mx.win, (base->winx / 2) - 100,
		(base->winy / 2) - 20, 0xffffff, "PLEASE WAIT...");
	mlx_put_image_to_window(base->mx.mlx, base->mx.win, base->mx.img, 0, 0);
}

t_fract	init_fract(t_base *base)
{
	t_fract	fr;

	fr.x = 0;
	fr.y = 0;
	fr.i = 0;
	fr.j = base->j;
	fr.mx = 0.0;
	fr.my = 0.0;
	fr.sx = 0.0;
	fr.sy = 0.0;
	fr.r = 230;
	fr.g = 105;
	fr.b = 250;
	fr.zoom = 1.0;
	fr.yolo = 0;
	fr.cr = 0.285;
	fr.maxi = 10;
	fr.ci = 0.1;
	fr.badtrip = 0;
	fr.posx = base->winx / 2;
	fr.posy = base->winy / 2;
	return (fr);
}

/*
** Make a copie of the struct fr for each thread
*/

t_fract	init_fracthr(t_base *base)
{
	t_fract	fr;

	fr.j = base->j;
	fr.i = base->frfr.i;
	fr.x = base->frfr.x;
	fr.y = base->frfr.y;
	fr.r = base->frfr.r;
	fr.g = base->frfr.g;
	fr.b = base->frfr.b;
	fr.mx = base->frfr.mx;
	fr.my = base->frfr.my;
	fr.sx = base->frfr.sx;
	fr.sy = base->frfr.sy;
	fr.cr = -base->frfr.cr;
	fr.ci = base->frfr.ci;
	fr.winx = base->winx;
	fr.winy = base->winy;
	fr.data = base->mx.data;
	fr.zoom = base->frfr.zoom;
	fr.maxi = base->frfr.maxi;
	fr.posx = base->frfr.posx;
	fr.posy = base->frfr.posy;
	fr.yolo = base->frfr.yolo;
	fr.badtrip = base->frfr.badtrip;
	return (fr);
}

void	init_tab(t_fract *fr)
{
	fr->tab[0] = &julia;
	fr->tab[1] = &mandelbrot;
	fr->tab[2] = &reversebrot;
	fr->tab[3] = &reversejulia;
	fr->tab[4] = &spark;
	fr->tab[5] = &zbli;
	fr->tab[6] = &plume;
}
