/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:58:03 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/16 15:59:22 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_flood(bool **filled_map)
{
	int	i;

	i = 0;
	while (filled_map[i])
	{
		free(filled_map[i]);
		i++;
	}
	free(filled_map);
}

static bool	floodfill(t_game *game, bool **filled_map, int i, int j)
{
	bool	is_surrounded;

	if (i < 0 || i >= find_double_array_len(game->map)
		|| j < 0 || j >= ft_strlen(game->map[i]) + 1)
		return (false);
	if (game->map[i][j] == '1' || filled_map[i][j] == true)
		return (true);
	else
		filled_map[i][j] = true;
	is_surrounded = true;
	is_surrounded &= floodfill(game, filled_map, i - 1, j);
	is_surrounded &= floodfill(game, filled_map, i + 1, j);
	is_surrounded &= floodfill(game, filled_map, i, j - 1);
	is_surrounded &= floodfill(game, filled_map, i, j + 1);
	return (is_surrounded);
}

int	check_map_surrounded(t_game *game)
{
	int		x;
	int		y;
	int		i;
	bool	**filled_map;
	bool	is_surrounded;

	x = game->pdata->pos_x;
	y = game->pdata->pos_y;
	filled_map = ft_calloc(find_double_array_len(game->map)
			+ 1, sizeof(bool *));
	i = -1;
	while (++i < find_double_array_len(game->map))
		filled_map[i] = ft_calloc(ft_strlen(game->map[i] + 1), sizeof(bool));
	is_surrounded = floodfill(game, filled_map, y, x);
	free_flood(filled_map);
	if (!is_surrounded)
		ft_exit("Map isn't surrounded by wall");
	return (1);
}
