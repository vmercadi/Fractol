/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:42:28 by vmercadi          #+#    #+#             */
/*   Updated: 2017/10/09 20:00:45 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Catch the mouse movments
*/

int		evmv_mouse(int x, int y, t_base *base)
{
	if (base->mouse)
	{
		base->frfr.sx = (double)(((long double)x - base->winx / 2) / 150);
		base->frfr.sy = (double)(((long double)y - base->winy / 2) / 150);
	}
	base->frfr.posx = x;
	base->frfr.posy = y;
	refresh(base);
	return (0);
}

/*
** Mouse events
*/

int		ev_mouse(int k, int x, int y, void *param)
{
	t_base *base;

	base = (t_base *)param;
	if (k == 1)
	{
		base->frfr.r = (x + y) * 255;
		base->frfr.g = (x + y) * 255;
		base->frfr.b = (x + y) * 255;
	}
	else if (k == 4 && base->frfr.zoom < 999999999999)
	{
		if (base->autoiter && base->frfr.maxi < 150)
			base->frfr.maxi++;
		base->frfr.zoom += 0.2 * base->frfr.zoom;
	}
	else if (k == 5 && base->frfr.zoom > 0.2)
	{
		if (base->autoiter && base->frfr.maxi > 2)
			base->frfr.maxi--;
		base->frfr.zoom -= 0.2 * base->frfr.zoom;
	}
	refresh(base);
	return (0);
}

/*
** Move events, iterations & zoom
*/

void	ev_move(int k, t_base *base)
{
	if ((k == 69 || k == 24) && base->frfr.zoom < 999999999999)
	{
		if (base->autoiter)
			base->frfr.maxi++;
		base->frfr.zoom += 0.2 * base->frfr.zoom;
	}
	else if ((k == 78 || k == 27) && base->frfr.zoom > 0.2)
	{
		if (base->autoiter && base->frfr.maxi > 2)
			base->frfr.maxi--;
		base->frfr.zoom -= 0.2 * base->frfr.zoom;
	}
	else if (k == 67 && base->frfr.maxi < 150)
		base->frfr.maxi++;
	else if (k == 75 && base->frfr.maxi > 2)
		base->frfr.maxi--;
	else if (k == 126)
		base->frfr.my -= 0.33 / base->frfr.zoom;
	else if (k == 125)
		base->frfr.my += 0.33 / base->frfr.zoom;
	else if (k == 124)
		base->frfr.mx += 0.33 / base->frfr.zoom;
	else if (k == 123)
		base->frfr.mx -= 0.33 / base->frfr.zoom;
	refresh(base);
}

/*
** Other events : Quit, choose fractal, change color, reinit
*/

void	ev_else(int k, t_base *base)
{
	if (k == 53)
		clean(base);
	else if (k == 15)
		base->frfr = init_fract(base);
	else if (k == 86)
		base->frfr.r += 1;
	else if (k == 87)
		base->frfr.g += 1;
	else if (k == 88)
		base->frfr.b += 1;
	else if (k == 83)
		base->frfr.r -= 1;
	else if (k == 84)
		base->frfr.g -= 1;
	else if (k == 85)
		base->frfr.b -= 1;
	else if (k == 49)
		base->mouse = (base->mouse == 1) ? 0 : 1;
	if (k == 43 && base->j > 0)
		base->j--;
	if (k == 47 && base->j < 6)
		base->j++;
	refresh(base);
}

/*
** Redirect the events and show/hide menus
*/

int		event(int k, void *param)
{
	t_base *base;

	base = (t_base *)param;
	if (k == 16)
		base->frfr.yolo = (base->frfr.yolo == 0) ? 1 : 0;
	else if (k == 51)
		base->frfr.badtrip = (base->frfr.badtrip == 0) ? 1 : 0;
	else if (k == 4)
		base->hide = (base->hide == 0) ? 1 : 0;
	else if (k == 36 || k == 76)
		base->autoiter = (base->autoiter == 0) ? 1 : 0;
	else if (k == 20)
		base->ui1 = (base->ui1 == 0) ? 1 : 0;
	else if (k == 21)
		base->ui2 = (base->ui2 == 0) ? 1 : 0;
	else if (k == 126 || k == 125 || k == 124 || k == 123 || k == 78 || k == 69
		|| k == 75 || k == 67 || k == 24 || k == 27)
		ev_move(k, base);
	else if (k == 83 || k == 84 || k == 85 || k == 49 || k == 53 || k == 15
		|| k == 43 || k == 47 || k == 86 || k == 87 || k == 88)
		ev_else(k, base);
	refresh(base);
	return (0);
}
