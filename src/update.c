/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:25:58 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/16 14:44:12 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_vertical(t_game *game, int x, int side, int y)
{
	while (++y < screenHeight)
	{
		game->draw->tex_y = (int)game->draw->tex_pos;
		if (y < game->draw->draw_s)
			game->draw->color = game->tex->ceilingc;
		else if (y > game->draw->draw_e)
			game->draw->color = game->tex->floorc;
		else
		{
			if (side == 0 && game->ray->ray_dirx < 0)
				game->draw->color = game->tex->ea->addr[game->draw->tex_h
					* game->draw->tex_y + game->draw->tex_x];
			else if (side == 0 && game->ray->ray_dirx >= 0)
				game->draw->color = game->tex->so->addr[game->draw->tex_h
					* game->draw->tex_y + game->draw->tex_x];
			if (side == 1 && game->ray->ray_diry < 0)
				game->draw->color = game->tex->no->addr[game->draw->tex_h
					* game->draw->tex_y + game->draw->tex_x];
			else if (side == 1 && game->ray->ray_diry >= 0)
				game->draw->color = game->tex->we->addr[game->draw->tex_h
					* game->draw->tex_y + game->draw->tex_x];
			game->draw->tex_pos += game->draw->step;
		}
		game->image->addr[y * screenWidth + x] = game->draw->color;
	}
}

int	update(t_game *game)
{
	int		x;
	int		stepX;
	int		stepY;
	int		side;
	
	x = -1;
	movements(game);
	while(++x < screenWidth)
	{
		calculate_ray(game, x);
		calculate_steps(game, &stepX, &stepY);
		hit_check(game, &side, stepX, stepY);
		calculate_pixels(game);
		if (side == 0)
			game->draw->wall_x = game->pdata->pos_y + game->ray->wall_dist * game->ray->ray_diry;
		else
			game->draw->wall_x = game->pdata->pos_x + game->ray->wall_dist * game->ray->ray_dirx;
		game->draw->wall_x -= (int)game->draw->wall_x;
		calculate_textures(game, side);
		draw_vertical(game, x, side, -1);
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);
	return (0);
}
