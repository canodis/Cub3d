/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:57:44 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/14 17:30:16 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_atoi_base(const char *str)
{
	int	i;
	int	n;
	int	len;
	int	result;

	i = 0;
	n = 1;
	result = 0;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		result *= 16;
		if (str[i] >= '0' && str[i] <= '9')
			result += str[i] - 48;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			result += str[i] - 55;
		else if (str[i] >= 'a' && str[i] <= 'z')
			result += str[i] - 87;
		i++;
	}
	return (result * n);
}

int	get_color(char *str)
{
	char	**double_array;
	int		result;

	double_array = ft_split(str, ',');
	result = atoi(double_array[0]) * 256 * 256
		+ atoi(double_array[1]) * 256 + atoi(double_array[2]);
	free_2d_array(double_array);
	return (result);
}

void	free_all(t_game *game)
{
	free(game->draw);
	free(game->image->addr);
	free(game->image->img);
	free(game->image);
	free(game->keys);
	free(game->pdata);
	free(game->ray);
	free(game->tex->ea->addr);
	free(game->tex->no->addr);
	free(game->tex->so->addr);
	free(game->tex->we->addr);
	free(game->tex->ea->img);
	free(game->tex->no->img);
	free(game->tex->so->img);
	free(game->tex->we->img);
	free(game->tex->ea);
	free(game->tex->no);
	free(game->tex->so);
	free(game->tex->we);
	free(game->tex);
	free(game->minimap);
	free_2d_array(game->map);
}
