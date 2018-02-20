/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:29:39 by vmercadi          #+#    #+#             */
/*   Updated: 2017/10/09 18:11:48 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Init and start the fractal needed
*/

void	*start_draw(void *tmp)
{
	t_fract *fr;
	int		x;

	fr = (t_fract*)tmp;
	x = fr->x;
	while (fr->y < fr->twiny)
	{
		fr->x = x;
		while (fr->x < fr->winx)
		{
			fr->nr = 0;
			fr->ni = 0;
			fr->ar = 0;
			fr->ai = 0;
			fr->i = 0;
			init_tab(fr);
			fr->tab[fr->j]((void *)fr);
			get_color(fr);
			px_img(fr);
			fr->x++;
		}
		fr->y++;
	}
	pthread_exit(0);
}

/*
** Algorithm for the Julia fractal
*/

void	julia(void *f)
{
	t_fract *fr;

	fr = (t_fract *)f;
	fr->nr = 1.5 * (fr->x - fr->winx / 2) /
		(0.5 * fr->zoom * fr->winx) + fr->mx;
	fr->ni = (fr->y - fr->winy / 2) / (0.5 * fr->zoom * fr->winy) + fr->my;
	fr->i = 0;
	fr->cr = 0.285 + fr->sx;
	fr->ci = 0.01 + fr->sy;
	while (fr->i < fr->maxi)
	{
		fr->ar = fr->nr;
		fr->ai = fr->ni;
		fr->nr = fr->ar * fr->ar - fr->ai * fr->ai + fr->cr;
		fr->ni = 2 * fr->ar * fr->ai + fr->ci;
		if ((fr->nr * fr->nr + fr->ni * fr->ni) > 4)
			break ;
		fr->i++;
	}
}

/*
** Algorithm for the Mandelbrot fractal
*/

void	mandelbrot(void *f)
{
	t_fract *fr;

	fr = (t_fract *)f;
	fr->cr = 1.5 * (fr->x - fr->winx / 2) /
		(0.5 * fr->zoom * fr->winx) + fr->mx;
	fr->ci = (fr->y - fr->winy / 2) / (0.5 * fr->zoom * fr->winy) + fr->my;
	while (fr->i < fr->maxi)
	{
		fr->ar = fr->nr + fr->sx;
		fr->ai = fr->ni + fr->sy;
		fr->nr = fr->ar * fr->ar - fr->ai * fr->ai + fr->cr;
		fr->ni = 2 * fr->ar * fr->ai + fr->ci;
		if ((fr->nr * fr->nr + fr->ni * fr->ni) > 4)
			break ;
		fr->i++;
	}
}
