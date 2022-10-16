#include "../include/cub3d.h"

void	*convert_xpm(t_game *game, char *path, void *free_item1)
{
	int	rand;

	free(free_item1);
	return (mlx_xpm_file_to_image((game)->mlx, path, &rand, &rand));
}

void	ft_exit(char *str)
{
	printf("%s",str);
	exit(1);
}

char *ft_read_map(int fd)
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
	printf("%s", result);
	exit(31);
	return (result);
}

void	get_adress(t_game *game)
{
	int	a;

	game->tex->ea->addr =  (int *)mlx_get_data_addr(game->tex->ea->img, &a, &a, &a);
	game->tex->we->addr =  (int *)mlx_get_data_addr(game->tex->we->img, &a, &a, &a);
	game->tex->no->addr =  (int *)mlx_get_data_addr(game->tex->no->img, &a, &a, &a);
	game->tex->so->addr =  (int *)mlx_get_data_addr(game->tex->so->img, &a, &a, &a);
}

void	map_inspection(char *str, int idx, int idy, t_game *game)
{
	char	**double_input;
	char	**split;
	int		y;
	char	*temp;
	int		map_y;

	y = -1;
	double_input = ft_split(str, '\n');
	map_y = find_double_array_len(double_input);
	while (++idy < map_y)
	{
		split = ft_split(double_input[idy], ' ');
		if (!ft_strcmp(split[0], "NO") && split[1])
			game->tex->no->img = convert_xpm(game, split[1], game->tex->no->img);
		else if (!ft_strcmp(split[0], "SO") && split[1])
			game->tex->so->img = convert_xpm(game, split[1], game->tex->so->img);
		else if (!ft_strcmp(split[0], "WE") && split[1])
			game->tex->we->img = convert_xpm(game, split[1], game->tex->we->img);
		else if (!ft_strcmp(split[0], "EA") && split[1])
			game->tex->ea->img = convert_xpm(game, split[1], game->tex->ea->img);
		else if (!ft_strcmp(split[0], "F") && split[1])
			game->tex->floorc = get_color(split[1]);
		else if (!ft_strcmp(split[0], "C") && split[1])
			game->tex->ceilingc = get_color(split[1]);
		else if (split[0][0] >= '0' && split[0][0] <= '9' && y == -1)
		{
			temp = fill_map(&double_input[idy], -1, &y, game);
			game->map = ft_split(temp, '\n');
			printf("%s\n", temp);
			exit(0);
			free(temp);
			check_map_surrounded(game);
			y = 0;
		}
		if (split || split[0])
			free_2d_array(split);
	}
	free_2d_array(double_input);
	get_adress(game);
}

bool	check_player(t_game *game, char p)
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
	else if (p == 'S')
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
				break;
			}
		}
		if (onetime)
			break;
	}
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
	set_playerpos(game);
	return (0);
}
