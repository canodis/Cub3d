/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:59:53 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/16 16:27:55 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	*convert_xpm(t_game *game, char *path, void *free_item1)
{
	int	rand;

	free(free_item1);
	return (mlx_xpm_file_to_image((game)->mlx, path, &rand, &rand));
}

void	ft_exit(char *str)
{
	printf("%s", str);
	exit(1);
}

void	get_adress(t_game *game)
{
	int	a;

	game->tex->ea->addr
		= (int *)mlx_get_data_addr(game->tex->ea->img, &a, &a, &a);
	game->tex->we->addr
		= (int *)mlx_get_data_addr(game->tex->we->img, &a, &a, &a);
	game->tex->no->addr
		= (int *)mlx_get_data_addr(game->tex->no->img, &a, &a, &a);
	game->tex->so->addr
		= (int *)mlx_get_data_addr(game->tex->so->img, &a, &a, &a);
}

char	*ft_read_map(int fd)
{
	int		rd_bytes;
	char	map[2];
	char	*value;

	value = NULL;
	rd_bytes = 1;
	while (rd_bytes != 0)
	{
		rd_bytes = read(fd, map, 1);
		map[rd_bytes] = '\0';
		value = ft_str_join(value, map);
	}
	return (value);
}

bool	checkmap_proccess(t_game *game, t_info *info)
{
	t_textures	*t;

	t = game->tex;
	if (!ft_strcmp(info->split[0], "NO") && info->split[1])
		t->no->img = convert_xpm(game, info->split[1], t->no->img);
	else if (!ft_strcmp(info->split[0], "SO") && info->split[1])
		t->so->img = convert_xpm(game, info->split[1], t->so->img);
	else if (!ft_strcmp(info->split[0], "WE") && info->split[1])
		t->we->img = convert_xpm(game, info->split[1], t->we->img);
	else if (!ft_strcmp(info->split[0], "EA") && info->split[1])
		t->ea->img = convert_xpm(game, info->split[1], t->ea->img);
	else if (!ft_strcmp(info->split[0], "F") && info->split[1])
		t->floorc = get_color(info->split[1]);
	else if (!ft_strcmp(info->split[0], "C") && info->split[1])
		t->ceilingc = get_color(info->split[1]);
	else
		return (false);
	return (true);
}
