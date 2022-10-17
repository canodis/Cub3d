/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculates.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:39:55 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/17 04:56:21 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calculate_ray(t_game *game, int x)
{
	game->ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray->ray_dirx = game->pdata->dir_x + (game->pdata->plane_x * game->ray->camera_x);
	game->ray->ray_diry = game->pdata->dir_y + (game->pdata->plane_y * game->ray->camera_x);
	game->ray->mapx = (int)game->pdata->pos_x;
	game->ray->mapy = (int)game->pdata->pos_y;
	if (game->ray->ray_dirx == 0)
		game->ray->delta_distx = 1;
	else
		game->ray->delta_distx = fabs(1 / game->ray->ray_dirx);
	if (game->ray->ray_diry == 0)
		game->ray->delta_disty = 1;
	else
		game->ray->delta_disty = fabs(1 / game->ray->ray_diry);
}

void	calculate_steps(t_game *game, int *step_x, int *step_y)
{
	if (game->ray->ray_dirx < 0)
	{
		*step_x = -1;
		game->ray->side_distx = (game->pdata->pos_x - game->ray->mapx) * game->ray->delta_distx;
	}
	else
	{
		*step_x = 1;
		game->ray->side_distx = (game->ray->mapx + 1.0 - game->pdata->pos_x) * game->ray->delta_distx;
	}
	if (game->ray->ray_diry < 0)
	{
		*step_y = -1;
		game->ray->side_disty = (game->pdata->pos_y - game->ray->mapy) * game->ray->delta_disty;
	}
	else
	{
		*step_y = 1;
		game->ray->side_disty = (game->ray->mapy + 1.0 - game->pdata->pos_y) * game->ray->delta_disty;
	}
}

void	calculate_pixels(t_game *game)
{
	game->draw->draw_s = -game->draw->line_h / 2 + SCREEN_HEIGHT / 2;
	game->draw->draw_e = game->draw->line_h / 2 + SCREEN_HEIGHT / 2;
	if (game->draw->draw_s < 0)
		game->draw->draw_s = 0;
	if (game->draw->draw_e >= SCREEN_HEIGHT)
		game->draw->draw_e = SCREEN_HEIGHT - 1;
}

void	calculate_textures(t_game *game, int side)
{
	game->draw->tex_x = game->draw->tex_w - (int)(game->draw->wall_x * game->draw->tex_w);
	game->draw->step = (double)game->draw->tex_h / game->draw->line_h;
	game->draw->tex_pos = (game->draw->draw_s - SCREEN_HEIGHT / 2 + game->draw->line_h / 2) * game->draw->step;
}

void	hit_check(t_game *game, int *side, int stepx, int stepy)
{
	while (1)
	{
		if (game->ray->side_distx < game->ray->side_disty)
		{
			game->ray->side_distx += game->ray->delta_distx;
			game->ray->mapx += stepx;
			*side = 0;
		}
		else
		{
			game->ray->side_disty += game->ray->delta_disty;
			game->ray->mapy += stepy;
			*side = 1;
		}
		if (game->map[game->ray->mapy][game->ray->mapx] == 49)
			break ;
	}
	if (*side == 0)
		game->ray->wall_dist = game->ray->side_distx - game->ray->delta_distx;
	else
		game->ray->wall_dist = game->ray->side_disty - game->ray->delta_disty;
	game->draw->line_h = (int)(SCREEN_HEIGHT / game->ray->wall_dist);
}
