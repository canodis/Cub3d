/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:09:01 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/16 14:55:23 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	ft_namecheck(char *str, char *find)
{
	char	*ber_str;

	ber_str = ft_strrchr(str, '.');
	if (ber_str && ft_strlen(ber_str) == 4
		&& ft_strncmp(ber_str, ".cub", 4) == 0)
		return (true);
	return (false);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2 && ft_namecheck(av[1], ".cub"))
	{
		check_map(&game, av[1]);
		mlx_hook(game.window, 2, 1L << 0, key_press, &game);
		mlx_hook(game.window, 3, 1L << 1, key_release, &game);
		mlx_do_sync(game.mlx);
		mlx_loop_hook(game.mlx, update, &game);
		mlx_loop(game. mlx);
	}
	else
		printf("Invalid arguments\n");
	return (0);
}
