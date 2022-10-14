#include "../include/cub3d.h"

void	go_east(t_game *game)
{
	if(game->map[(int)(game->pdata->pos_y)][(int)(game->pdata->pos_x
		+ game->pdata->plane_x * game->pdata->speed)] != 49)
		game->pdata->pos_x += game->pdata->plane_x * game->pdata->speed;
	if (game->map[(int)(game->pdata->pos_y + game->pdata->plane_y
		* game->pdata->speed)][(int)(game->pdata->pos_x)] != 49)
		game->pdata->pos_y += game->pdata->plane_y * game->pdata->speed;
}

void	go_west(t_game *game)
{
	if (game->map[(int)(game->pdata->pos_y - game->pdata->plane_y
		* game->pdata->speed)][(int)game->pdata->pos_x] != 49)
		game->pdata->pos_y -= game->pdata->plane_y * game->pdata->speed;
	if(game->map[(int)(game->pdata->pos_y)][(int)(game->pdata->pos_x
		- game->pdata->plane_x* game->pdata->speed)] != 49)
		game->pdata->pos_x -= game->pdata->plane_x * game->pdata->speed;
}

void	go_north(t_game *game)
{
	if(game->map[(int)game->pdata->pos_y][(int)(game->pdata->pos_x
		+ game->pdata->dir_x * game->pdata->speed)] != 49)
		game->pdata->pos_x += game->pdata->dir_x * game->pdata->speed;
	if(game->map[(int)(game->pdata->pos_y + game->pdata->dir_y
		* game->pdata->speed)][(int)game->pdata->pos_x] != 49)
		game->pdata->pos_y += game->pdata->dir_y * game->pdata->speed;
}

void	go_south(t_game *game)
{
	if(game->map[(int)game->pdata->pos_y][(int)(game->pdata->pos_x
		- game->pdata->dir_x * game->pdata->speed)] != 49)
		game->pdata->pos_x -= game->pdata->dir_x * game->pdata->speed;
	if(game->map[(int)(game->pdata->pos_y - game->pdata->dir_y
		* game->pdata->speed)][(int)(game->pdata->pos_x)] != 49)
		game->pdata->pos_y -= game->pdata->dir_y * game->pdata->speed;
}