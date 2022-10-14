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

void	rotate_right(t_player *p)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->dir_x;
	p->dir_x = p->dir_x * cos(-p->rot_speed) - p->dir_y * sin(-p->rot_speed);
	p->dir_y = oldDirX * sin(-p->rot_speed) + p->dir_y * cos(-p->rot_speed);
	oldPlaneX = p->plane_x;
	p->plane_x = p->plane_x * cos(-p->rot_speed)
		- p->plane_y * sin(-p->rot_speed);
	p->plane_y = oldPlaneX * sin(-p->rot_speed)
		+ p->plane_y * cos(-p->rot_speed);
}