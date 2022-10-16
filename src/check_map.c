/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:59:48 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/16 16:26:55 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_playerpos(t_game *game)
{
	int		y;
	int		x;
	bool	onetime;

	onetime = false;
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (check_player(game, game->map[y][x]))
			{
				game->pdata->pos_x = x + 0.5f;
				game->pdata->pos_y = y + 0.5f;
				onetime = true;
				break ;
			}
		}
		if (onetime)
			break ;
	}
}

bool	anything(char *s1, char *s2)
{
	int	len;

	len = ft_strlen(s1) - ft_strlen(s2);
	if (len > 0)
	{
		len = ft_strlen(s2);
		while (s1[len])
		{
			if (s1[len] != ' ' && s1[len] != '1')
				return (false);
			len++;
		}
	}
	else
	{
		len = ft_strlen(s1);
		while (s2[len])
		{
			if (s2[len] != '1' && s2[len] != ' ')
				return (false);
			len++;
		}
	}
	return (true);
}

char	*fill_map(char **str, int x, int *y, t_game *game)
{
	char	*result;
	int		idx;

	idx = 0;
	result = malloc(sizeof(char) * len_2d_into(str) + 1);
	while (++(*y) < find_double_array_len(str))
	{
		x = -1;
		while (++x < ft_strlen(str[*y]))
		{
			if (str[*y][x] == ' ')
				result[idx++] = '0';
			else if (!ft_strchr("NSEW01", str[*y][x]))
			{
				result[idx] = '\0';
				return (result);
			}
			else
				result[idx++] = str[*y][x];
		}
		if ((*y) + 1 < find_double_array_len(str))
			result[idx++] = '\n';
	}
	result[idx] = '\0';
	return (result);
}

void	map_inspection(char *str, int idx, int idy, t_game *game)
{
	t_info	info;

	info.y = -1;
	info.double_input = ft_split(str, '\n');
	info.map_y = find_double_array_len(info.double_input);
	while (++idy < info.map_y)
	{
		info.split = ft_split(info.double_input[idy], ' ');
		if (checkmap_proccess(game, &info))
			;
		else if (info.split[0][0] >= '0'
			&& info.split[0][0] <= '9' && info.y == -1)
		{
			info.temp = fill_map(&info.double_input[idy], -1, &info.y, game);
			game->map = ft_split(info.temp, '\n');
			free(info.temp);
			set_playerpos(game);
			check_map_surrounded(game);
			info.y = 0;
		}
		if (info.split || info.split[0])
			free_2d_array(info.split);
	}
	free_2d_array(info.double_input);
	get_adress(game);
}

bool	check_map(t_game *game, char *str)
{
	int		fd;
	char	*map;

	fd = open(str, O_RDWR);
	if (fd < 0)
	{
		printf("Wrong map name !");
		exit(0);
	}
	init_all(game);
	map = ft_read_map(fd);
	map_inspection(map, 0, -1, game);
	close(fd);
	free(map);
	return (0);
}
