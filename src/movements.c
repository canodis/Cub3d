/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:49:17 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/16 15:52:30 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	go_east(t_game *game)
{
	if (game->map[(int)(game->pdata->pos_y)][(int)(game->pdata->pos_x
		+ game->pdata->plane_x * game->pdata->speed)] != 49)
		game->pdata->pos_x += game->pdata->plane_x * game->pdata->speed;
	if (game->map[(int)(game->pdata->pos_y + game->pdata->plane_y
			* game->pdata->speed)][(int)(game->pdata->pos_x)] != 49)
		game->pdata->pos_y += game->pdata->plane_y * game->pdata->speed;
}

void	go_west(t_game *game)
{
	if (game->map[(int)(game->pdata->pos_y - game->pdata->plane_y
			* game->pdata->speed)][(int)game->pdata->pos_x] != 49)
		game->pdata->pos_y -= game->pdata->plane_y * game->pdata->speed;
	if (game->map[(int)(game->pdata->pos_y)][(int)(game->pdata->pos_x
			- game->pdata->plane_x * game->pdata->speed)] != 49)
		game->pdata->pos_x -= game->pdata->plane_x * game->pdata->speed;
}

void	go_north(t_game *game)
{
	if (game->map[(int)game->pdata->pos_y][(int)(game->pdata->pos_x
		+ game->pdata->dir_x * game->pdata->speed)] != 49)
		game->pdata->pos_x += game->pdata->dir_x * game->pdata->speed;
	if (game->map[(int)(game->pdata->pos_y + game->pdata->dir_y
			* game->pdata->speed)][(int)game->pdata->pos_x] != 49)
		game->pdata->pos_y += game->pdata->dir_y * game->pdata->speed;
}

void	go_south(t_game *game)
{
	if (game->map[(int)game->pdata->pos_y][(int)(game->pdata->pos_x
		- game->pdata->dir_x * game->pdata->speed)] != 49)
		game->pdata->pos_x -= game->pdata->dir_x * game->pdata->speed;
	if (game->map[(int)(game->pdata->pos_y - game->pdata->dir_y
			* game->pdata->speed)][(int)(game->pdata->pos_x)] != 49)
		game->pdata->pos_y -= game->pdata->dir_y * game->pdata->speed;
}

void	rotate_right(t_player *p)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = p->dir_x;
	p->dir_x = p->dir_x * cos(-p->rot_speed) - p->dir_y * sin(-p->rot_speed);
	p->dir_y = old_dirx * sin(-p->rot_speed) + p->dir_y * cos(-p->rot_speed);
	old_planex = p->plane_x;
	p->plane_x = p->plane_x * cos(-p->rot_speed)
		- p->plane_y * sin(-p->rot_speed);
	p->plane_y = old_planex * sin(-p->rot_speed)
		+ p->plane_y * cos(-p->rot_speed);
}
