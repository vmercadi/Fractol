/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:43:11 by vmercadi          #+#    #+#             */
/*   Updated: 2017/10/09 19:39:13 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTOL_H
# define __FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <pthread.h>
# include <limits.h>
# define NBTH 8
# define W 0xffffff
# define G 0x00ff00
# define WINX 800
# define WINY 800

typedef void			(*t_ft) (void*);

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	int					bpp;
	int					*data;
	int					endian;
	int					sizeline;
}						t_mlx;

typedef struct			s_fract
{
	t_ft				tab[7];
	int					x;
	int					y;
	int					i;
	int					j;
	int					maxi;
	int					maxre;
	int					maxim;
	int					minre;
	int					minim;
	int					winx;
	int					winy;
	int					posx;
	int					posy;
	int					yolo;
	int					badtrip;
	int					twiny;
	int					*data;
	double				sx;
	double				sy;
	double				cr;
	double				ci;
	double				nr;
	double				ni;
	double				ar;
	double				ai;
	double				mx;
	double				my;
	double				zoom;
	unsigned int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_fract;

typedef struct			s_base
{
	struct s_mlx		mx;
	struct s_fract		frfr;
	struct s_fract		fr[NBTH];
	char				*name;
	char				*av;
	int					j;
	int					ui1;
	int					ui2;
	int					ui3;
	int					winx;
	int					winy;
	int					mouse;
	int					hide;
	int					autoiter;
	int					win_size;
}						t_base;

/*
** Start of the program			|  fractol.c
*/

void					fractol(t_base *base);

/*
** Fractals algorithms			|  fractals.c
*/

void					*start_draw(void *base);
void					julia(void *fr);
void					mandelbrot(void *fr);

/*
** Other fractals algorithms	|  fractals2.c
*/

void					reversebrot(void *fr);
void					reversejulia(void *fr);
void					spark(void *fr);
void					zbli(void *fr);
void					plume(void *fr);

/*
** UI, colors and display		| display.c
*/

void					px_img(t_fract *fr);
void					get_color(t_fract *fr);
void					ui(t_base *base);
void					ui1(t_base *base);
void					ui2(t_base *base);
void					ui3(t_base *base);

/*
** All the events functions		|  event.c
*/

void					refresh(t_base *base);
int						event(int keycode, void *param);
void					ev_move(int k, t_base *base);
void					ev_else(int k, t_base *base);
int						ev_mouse(int k, int x, int y, void *param);
int						evmv_mouse(int x, int y, t_base *base);

/*
** The init functions			|  init.c
*/

void					init_base(t_base *base, char *av);
void					init_tab(t_fract *fr);
t_fract					init_fract(t_base *base);
t_fract					init_fracthr(t_base *base);

/*
** Various functions			|  utils.c
*/

void					error(int e);
int						clean(t_base *base);
void					mthread(t_base *base);
void					get_name(t_base *base);
int						get_fractal(char *av);

#endif
