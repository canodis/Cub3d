/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:01:47 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/16 16:17:26 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	east_west(t_game *game, char p)
{
	if (p == 'E')
	{
		game->pdata->dir_x = 0.00;
		game->pdata->dir_y = 1.00;
		game->pdata->plane_x = 0.66;
		game->pdata->plane_y = 0;
		return (true);
	}
	else if (p == 'W')
	{
		game->pdata->dir_x = 0.00;
		game->pdata->dir_y = -1.00;
		game->pdata->plane_x = -0.66;
		game->pdata->plane_y = 0;
		return (true);
	}
	return (false);
}

static bool	south_north(t_game *game, char p)
{
	if (p == 'S')
	{
		game->pdata->dir_x = -1.00;
		game->pdata->dir_y = 0.00;
		game->pdata->plane_x = 0;
		game->pdata->plane_y = 0.66;
		return (true);
	}
	else if (p == 'N')
	{
		game->pdata->dir_x = 1.00;
		game->pdata->dir_y = 0.00;
		game->pdata->plane_x = 0;
		game->pdata->plane_y = -0.66;
		return (true);
	}
	return (false);
}

bool	check_player(t_game *game, char p)
{
	if (east_west(game, p))
		return (true);
	if (south_north(game, p))
		return (true);
	return (false);
}
