#include "../include/cub3d.h"

void *convert_xpm(t_game *game, char *path)
{
	int	rand;

	return (mlx_xpm_file_to_image((game)->mlx, path, &rand, &rand));
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
	int len;

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

bool	check_walls(t_game *game, int x, int y, char **str)
{
	while (++y < find_double_array_len(str))
	{
		x = -1;
		while (++x < ft_strlen(str[y]))
		{
			if (str[y][x] == ' ')
				x++;
			else if (str[y][x] != '1' && (y == 0 || y == ft_strlen(str[y]) - 1))
				ft_exit("walss ilk if");
			else if (str[y][x] != '1' && (x == 0 || x == ft_strlen(str[y]) - 1))
				ft_exit("walls second if");
			else if (!ft_strchr("NSEW01", str[y][x]))
				ft_exit("onje walls");
			else if (str[y + 1] && !anything(str[y], str[y + 1]))
				ft_exit("anything");
		}
	}
	return (true);
}

char	*fill_map(char **str, int x, int *y, t_game *game)
{
	char	*result;
	int		idx;

	idx = 0;
	result = malloc(sizeof(char) * no_blank_len(str) + 1);
	check_walls(game, -1, -1, str);
	while (++(*y) < find_double_array_len(str))
	{
		x = -1;
		while (++x < ft_strlen(str[*y]))
		{
			if (str[*y][x] == ' ')
				continue;
			else if (!ft_strchr("NSEW01", str[*y][x]))
			{
				result[idx] = '\0';
				return (result);
			}
			result[idx++] = str[*y][x];
		}
		if ((*y) + 1 < find_double_array_len(str))
			result[idx++] = '\n';
	}
	result[idx] = '\0';
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
			game->tex->no->img = convert_xpm(game, split[1]);
		else if (!ft_strcmp(split[0], "SO") && split[1])
			game->tex->so->img = convert_xpm(game, split[1]);
		else if (!ft_strcmp(split[0], "WE") && split[1])
			game->tex->we->img = convert_xpm(game, split[1]);
		else if (!ft_strcmp(split[0], "EA") && split[1])
			game->tex->ea->img = convert_xpm(game, split[1]);
		else if (!ft_strcmp(split[0], "F") && split[1])
			game->tex->floorc = ft_atoi(split[1]);
		else if (!ft_strcmp(split[0], "C") && split[1])
			game->tex->ceilingc = ft_atoi(split[1]);
		else if (split[0][0] >= '0' && split[0][0] <= '9' && y == -1)
		{
			temp = fill_map(&double_input[idy], -1, &y, game);
			game->map = ft_split(temp, '\n');
			free(temp);
			y = 0;
		}
		free_2d_array(split);
	}
	free_2d_array(double_input);
	get_adress(game);
}

void	init_info(t_game *game)
{
	int a;

	game->tex = malloc(sizeof(t_textures));
	game->tex->ea = malloc(sizeof(t_data));
	game->tex->we = malloc(sizeof(t_data));
	game->tex->no = malloc(sizeof(t_data));
	game->tex->so = malloc(sizeof(t_data));
	
	game->tex->ceilingc = 0x17F662;
	game->tex->floorc = 0x33ffff;
}

bool	check_map(t_game *game, char *str)
{
	int		fd;
	char	*map;

	fd = open(str, O_RDWR);
	if (fd <= 0)
		ft_exit("open error");
	map = ft_read_map(fd);
	init_info(game);
	map_inspection(map, 0, -1, game);
	close(fd);
	free(map);
}