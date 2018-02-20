/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:48:54 by vmercadi          #+#    #+#             */
/*   Updated: 2017/10/09 18:15:19 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Multi-threading
*/

void	mthread(t_base *base)
{
	pthread_t	th[NBTH];
	int			i;
	int			size;

	i = 0;
	size = base->winy / NBTH;
	while (i < NBTH)
	{
		base->fr[i] = init_fracthr(base);
		base->fr[i].y = i * size;
		base->fr[i].twiny = (i + 1) * size;
		if (pthread_create(&th[i], NULL, start_draw, (void *)&base->fr[i]))
			error(4);
		i++;
	}
	i = 0;
	while (i < NBTH)
		pthread_join(th[i++], NULL);
}

/*
** All the error messages
*/

void	error(int e)
{
	if (e == 0 || e == 1)
	{
		ft_putendl_fd("Usage : ./fractol FractalName", 2);
		exit(1);
	}
	ft_putstr_fd("Error : ", 2);
	if (e == 2)
		ft_putendl_fd("Wrong fractal name.", 2);
	else if (e == 3)
		ft_putendl_fd("ECHEC CRITIK", 2);
	else if (e == 4)
		ft_putendl_fd("Multithreading failed.", 2);
	exit(1);
}

/*
** Free all the tabs needed
*/

int		clean(t_base *base)
{
	mlx_destroy_window(base->mx.mlx, base->mx.win);
	mlx_destroy_image(base->mx.mlx, base->mx.img);
	ft_strdel(&base->name);
	ft_strdel(&base->av);
	exit(0);
	return (0);
}

/*
** Return the the letter corresponding to the fractal
*/

int		get_fractal(char *av)
{
	int j;

	j = 0;
	if (!ft_strcmp(av, "Julia") || !ft_strcmp(av, "j") ||
		!ft_strcmp(av, "julia") || !ft_strcmp(av, "J"))
		j = 0;
	else if (!ft_strcmp(av, "Mandelbrot") || !ft_strcmp(av, "m") ||
			!ft_strcmp(av, "mandelbrot") || !ft_strcmp(av, "M"))
		j = 1;
	else if (!ft_strcmp(av, "Reversebrot") || !ft_strcmp(av, "rb") ||
			!ft_strcmp(av, "reversebrot") || !ft_strcmp(av, "RB"))
		j = 2;
	else if (!ft_strcmp(av, "Reversejulia") || !ft_strcmp(av, "rj") ||
			!ft_strcmp(av, "reversejulia") || !ft_strcmp(av, "RJ"))
		j = 3;
	else if (!ft_strcmp(av, "Spark") || !ft_strcmp(av, "s") ||
			!ft_strcmp(av, "spark") || !ft_strcmp(av, "S"))
		j = 4;
	else if (!ft_strcmp(av, "zbli") || !ft_strcmp(av, "Z"))
		j = 5;
	else if (!ft_strcmp(av, "plumes") || !ft_strcmp(av, "P"))
		j = 6;
	else
		error(2);
	return (j);
}

/*
** Return the name of the current fractal
*/

void	get_name(t_base *base)
{
	if (base->j == 0)
		base->name = ft_strdup("Julia");
	else if (base->j == 1)
		base->name = ft_strdup("Mandelbrot");
	else if (base->j == 2)
		base->name = ft_strdup("Reversebrot");
	else if (base->j == 3)
		base->name = ft_strdup("Reversejulia");
	else if (base->j == 4)
		base->name = ft_strdup("Spark");
	else if (base->j == 5)
		base->name = ft_strdup("Zbli");
	else if (base->j == 6)
		base->name = ft_strdup("Plumes");
}
