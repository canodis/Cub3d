#include "../include/cub3d.h"

void	free_all(t_game *game)
{
	free(game->draw);
	free(game->pdata);
	free(game->ray);
	free(game->tex);
}

void	rotate_cam(int keycode, t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	if (keycode == 0)
	{
		oldDirX = game->pdata->dir_x;
		game->pdata->dir_x = game->pdata->dir_x * cos(game->pdata->rot_speed)- game->pdata->dir_y * sin(game->pdata->rot_speed);
		game->pdata->dir_y = oldDirX * sin(game->pdata->rot_speed) + game->pdata->dir_y * cos(game->pdata->rot_speed);
		oldPlaneX = game->pdata->plane_x;
		game->pdata->plane_x = game->pdata->plane_x * cos(game->pdata->rot_speed) - game->pdata->plane_y * sin(game->pdata->rot_speed);
		game->pdata->plane_y = oldPlaneX * sin(game->pdata->rot_speed) + game->pdata->plane_y * cos(game->pdata->rot_speed);
	}
	if (keycode == 2)
	{
		oldDirX = game->pdata->dir_x;
		game->pdata->dir_x = game->pdata->dir_x * cos(-game->pdata->rot_speed) - game->pdata->dir_y * sin(-game->pdata->rot_speed);
		game->pdata->dir_y = oldDirX * sin(-game->pdata->rot_speed) + game->pdata->dir_y * cos(-game->pdata->rot_speed);
		oldPlaneX = game->pdata->plane_x;
		game->pdata->plane_x = game->pdata->plane_x * cos(-game->pdata->rot_speed) - game->pdata->plane_y * sin(-game->pdata->rot_speed);
		game->pdata->plane_y = oldPlaneX * sin(-game->pdata->rot_speed) + game->pdata->plane_y * cos(-game->pdata->rot_speed);
	}
}

int	key_events(int keycode, t_game *game)
{
	rotate_cam(keycode, game);
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->window);
		free_all(game);
		exit(0);
	}
	if (keycode == 13)
	{
		if(map[(int)(game->pdata->pos_x + game->pdata->dir_x * 0.5f)][(int)game->pdata->pos_y] == 0)
			game->pdata->pos_x += game->pdata->dir_x * 0.5f;
		if(map[(int)game->pdata->pos_x][(int)(game->pdata->pos_y + game->pdata->dir_y * 0.5f)] == 0)
			game->pdata->pos_y += game->pdata->dir_y * 0.5f;
	}
	if (keycode == 1)
	{
		if(map[(int)(game->pdata->pos_x - game->pdata->dir_x * 0.5f)][(int)game->pdata->pos_y] == 0)
			game->pdata->pos_x -= game->pdata->dir_x * 0.5f;
		if(map[(int)(game->pdata->pos_x)][(int)(game->pdata->pos_y - game->pdata->dir_y * 0.5f)] == 0)
			game->pdata->pos_y -= game->pdata->dir_y * 0.5f;
	}
	return (0);
}