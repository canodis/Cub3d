/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:53:46 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/14 17:36:29 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_cam(t_game *game)
{
	double		oldDirX;
	double		oldPlaneX;
	t_player	*p;

	p = game->pdata;
	if (game->keys->left_key)
	{
		oldDirX = p->dir_x;
		p->dir_x = p->dir_x * cos(p->rot_speed) - p->dir_y * sin(p->rot_speed);
		p->dir_y = oldDirX * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
		oldPlaneX = p->plane_x;
		p->plane_x = p->plane_x * cos(p->rot_speed)
			- p->plane_y * sin(p->rot_speed);
		p->plane_y = oldPlaneX * sin(p->rot_speed)
			+ p->plane_y * cos(p->rot_speed);
	}
	if (game->keys->right_key)
		rotate_right(p);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->window);
		free_all(game);
		// while (1);
		exit(0);
	}
	if (keycode == 13)
		game->keys->w_key = true;
	if (keycode == 1)
		game->keys->s_key = true;
	if (keycode == 123)
		game->keys->left_key = true;
	if (keycode == 124)
		game->keys->right_key = true;
	if (keycode == 49)
		game->keys->shift_key = true;
	if (keycode == 0)
		game->keys->a_key = true;
	if (keycode == 2)
		game->keys->d_key = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys->w_key = false;
	if (keycode == 1)
		game->keys->s_key = false;
	if (keycode == 123)
		game->keys->left_key = false;
	if (keycode == 124)
		game->keys->right_key = false;
	if (keycode == 49)
		game->keys->shift_key = false;
	if (keycode == 0)
		game->keys->a_key = false;
	if (keycode == 2)
		game->keys->d_key = false;
	return (0);
}

void	movements(t_game *game)
{
	rotate_cam(game);
	if (game->keys->d_key)
		go_east(game);
	if (game->keys->a_key)
		go_west(game);
	if (game->keys->w_key)
		go_north(game);
	if (game->keys->s_key)
		go_south(game);
	if (game->keys->shift_key)
		game->pdata->speed = 0.1f;
	else
		game->pdata->speed = 0.05f;
}