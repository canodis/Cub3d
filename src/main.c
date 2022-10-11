/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:09:01 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/11 16:44:41 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int ac, char **av)
{
	t_game	game;

	init_all(&game);
	check_map(&game, av[1]);
	mlx_hook(game.window,2, 1L<<0, key_press, &game);
	mlx_hook(game.window,3, 1L<<1, key_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game. mlx);
	return (31);
}