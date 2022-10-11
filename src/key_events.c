#include "../include/cub3d.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
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

void	rotate_cam(t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	if (game->keys->left_key)
	{
		oldDirX = game->pdata->dir_x;
		game->pdata->dir_x = game->pdata->dir_x * cos(game->pdata->rot_speed) - game->pdata->dir_y * sin(game->pdata->rot_speed);
		game->pdata->dir_y = oldDirX * sin(game->pdata->rot_speed) + game->pdata->dir_y * cos(game->pdata->rot_speed);
		oldPlaneX = game->pdata->plane_x;
		game->pdata->plane_x = game->pdata->plane_x * cos(game->pdata->rot_speed) - game->pdata->plane_y * sin(game->pdata->rot_speed);
		game->pdata->plane_y = oldPlaneX * sin(game->pdata->rot_speed) + game->pdata->plane_y * cos(game->pdata->rot_speed);
	}
	if (game->keys->right_key)
	{
		oldDirX = game->pdata->dir_x;
		game->pdata->dir_x = game->pdata->dir_x * cos(-game->pdata->rot_speed) - game->pdata->dir_y * sin(-game->pdata->rot_speed);
		game->pdata->dir_y = oldDirX * sin(-game->pdata->rot_speed) + game->pdata->dir_y * cos(-game->pdata->rot_speed);
		oldPlaneX = game->pdata->plane_x;
		game->pdata->plane_x = game->pdata->plane_x * cos(-game->pdata->rot_speed) - game->pdata->plane_y * sin(-game->pdata->rot_speed);
		game->pdata->plane_y = oldPlaneX * sin(-game->pdata->rot_speed) + game->pdata->plane_y * cos(-game->pdata->rot_speed);
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->window);
		free_all(game);
		while (1);
		exit(0);
	}
	if (keycode == 13)
		game->keys->w_key = true;
	if (keycode == 1)
		game->keys->s_key = true;
	if (keycode == 123)
		game->keys->left_key = true;
	if (keycode == 124)
		game->keys->right_key = true;
	if (keycode == 49)
		game->keys->shift_key = true;
	if (keycode == 0)
		game->keys->a_key = true;
	if (keycode == 2)
		game->keys->d_key = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys->w_key = false;
	if (keycode == 1)
		game->keys->s_key = false;
	if (keycode == 123)
		game->keys->left_key = false;
	if (keycode == 124)
		game->keys->right_key = false;
	if (keycode == 49)
		game->keys->shift_key = false;
	if (keycode == 0)
		game->keys->a_key = false;
	if (keycode == 2)
		game->keys->d_key = false;
	return (0);
}

void	movements(t_game *game)
{
	rotate_cam(game);
	if (game->keys->w_key)
	{
		if(game->map[(int)game->pdata->pos_y][(int)(game->pdata->pos_x + game->pdata->dir_x * game->pdata->speed)] != 49)
			game->pdata->pos_x += game->pdata->dir_x * game->pdata->speed;
		if(game->map[(int)(game->pdata->pos_y + game->pdata->dir_y * game->pdata->speed)][(int)game->pdata->pos_x] != 49)
			game->pdata->pos_y += game->pdata->dir_y * game->pdata->speed;
	}
	if (game->keys->s_key)
	{
		if(game->map[(int)game->pdata->pos_y][(int)(game->pdata->pos_x - game->pdata->dir_x * game->pdata->speed)] != 49)
			game->pdata->pos_x -= game->pdata->dir_x * game->pdata->speed;
		if(game->map[(int)(game->pdata->pos_y - game->pdata->dir_y * game->pdata->speed)][(int)(game->pdata->pos_x)] != 49)
			game->pdata->pos_y -= game->pdata->dir_y * game->pdata->speed;
	}
	if (game->keys->a_key)
	{
		if (game->map[(int)(game->pdata->pos_y - game->pdata->plane_y * game->pdata->speed)][(int)game->pdata->pos_x] != 49)
			game->pdata->pos_y -= game->pdata->plane_y * game->pdata->speed;
		if(game->map[(int)(game->pdata->pos_y)][(int)(game->pdata->pos_x - game->pdata->plane_x * game->pdata->speed)] != 49)
			game->pdata->pos_x -= game->pdata->plane_x * game->pdata->speed;
	}
	if (game->keys->d_key)
	{
		if(game->map[(int)(game->pdata->pos_y)][(int)(game->pdata->pos_x + game->pdata->plane_x * game->pdata->speed)] != 49)
			game->pdata->pos_x += game->pdata->plane_x * game->pdata->speed;
		if (game->map[(int)(game->pdata->pos_y + game->pdata->plane_y * game->pdata->speed)][(int)(game->pdata->pos_x)] != 49)
			game->pdata->pos_y += game->pdata->plane_y * game->pdata->speed;
	}
	if (game->keys->shift_key)
		game->pdata->speed = 0.1f;
	else
		game->pdata->speed = 0.05f;

}