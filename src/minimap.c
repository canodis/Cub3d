/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:55:08 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/15 17:45:43 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	reset_values(t_game *game)
{
	game->minimap->x = -1;
	game->minimap->y = -1;
	game->minimap->o = 0;
	game->minimap->py = 0;
	game->minimap->px = 0;
	game->minimap->i = 0;
}

static void	render_minimap(t_game *game, int color, int pixels_to_draw)
{
	game->minimap->px = game->minimap->x * pixels_to_draw;
	game->minimap->o = 0;
	while (game->minimap->o < pixels_to_draw -1)
	{
		game->image->addr[game->minimap->py
			* screenWidth + game->minimap->px] = color;
		game->minimap->px++;
		game->minimap->o++;
	}
}

static void	draw_minimap(t_game *game, int pixels_to_draw)
{
	char	c;

	c = game->map[game->minimap->y][game->minimap->x];
	if (c == '1')
		render_minimap(game, 0x00F0F0F0, pixels_to_draw);
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		render_minimap(game, 0, pixels_to_draw);
	if ((game->minimap->y == (int)game->pdata->pos_y)
		&& (game->minimap->x == (int)game->pdata->pos_x))
		render_minimap(game, 0x00FF0000, pixels_to_draw);
}

void	minimap(t_game *game)
{
	int	pixels_to_draw;

	pixels_to_draw = 10;
	reset_values(game);
	while (game->map[++game->minimap->y])
	{
		game->minimap->x = -1;
		while (game->map[game->minimap->y][++game->minimap->x])
		{
			game->minimap->i = 0;
			game->minimap->py = game->minimap->y * pixels_to_draw;
			while (game->minimap->i < pixels_to_draw - 1)
			{
				draw_minimap(game, pixels_to_draw);
				game->minimap->i++;
				game->minimap->py++;
			}
		}
	}
}
