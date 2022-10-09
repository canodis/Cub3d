/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:26:43 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/09 15:11:14 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures(t_game *game)
{
	int	a;

	game->tex = malloc(sizeof(t_textures));
	game->tex->ea = malloc(sizeof(t_data));
	game->tex->we = malloc(sizeof(t_data));
	game->tex->no = malloc(sizeof(t_data));
	game->tex->so = malloc(sizeof(t_data));
	game->tex->ea->img = mlx_xpm_file_to_image(game->mlx,
			"sprites/brick.xpm", &a, &a);
	game->tex->we->img = mlx_xpm_file_to_image(game->mlx,
			"sprites/brick.xpm", &a, &a);
	game->tex->no->img = mlx_xpm_file_to_image(game->mlx,
			"sprites/brick.xpm", &a, &a);
	game->tex->so->img = mlx_xpm_file_to_image(game->mlx,
			"sprites/brick.xpm", &a, &a);
	game->tex->ceilingc = 0x33ccff;
	game->tex->floorc = 0x33cc33;
}

void	init_keys(t_game *game)
{
	game->keys = malloc(sizeof(t_keyboard));
	game->keys->left_key = false;
	game->keys->right_key = false;
	game->keys->w_key = false;
	game->keys->a_key = false;
	game->keys->s_key = false;
	game->keys->d_key = false;
	game->keys->shift_key = false;
}

void	init_minimap(t_game *game)
{
	game->minimap = malloc(sizeof(t_minimap));
	game->minimap->x = 0;
	game->minimap->y = 0;
	game->minimap->o = 0;
	game->minimap->u = 0;
	game->minimap->py = 0;
	game->minimap->px = 0;
}
