#include "../include/cub3d.h"

void	init_mlx(t_game *game)
{
	int	a;

	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, screenWidth, screenHeight, "c3");
	game->image = malloc(sizeof(t_data));
	game->image->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->image->addr = (int *)mlx_get_data_addr(game->image->img,
			&a, &a, &a);
}

void	init_player_data(t_game *game)
{
	game->pdata = malloc(sizeof(t_player));
	game->pdata->pos_x = 4;
	game->pdata->pos_y = 5;
	game->pdata->dir_x = -1;
	game->pdata->dir_y = 0;
	game->pdata->plane_x = 0;
	game->pdata->plane_y = 3.14159 / 4.0;
	game->pdata->rot_speed = 0.03f;
	game->pdata->speed = 0.05f;
}

void	init_ray_data(t_game *game)
{
	game->ray = malloc(sizeof(t_ray));
	game->ray->camera_x = 0;
	game->ray->delta_distx = 0;
	game->ray->delta_disty = 0;
	game->ray->mapx = 0;
	game->ray->mapy = 0;
	game->ray->ray_dirx = 0;
	game->ray->ray_diry = 0;
	game->ray->side_distx = 0;
	game->ray->side_disty = 0;
	game->ray->wall_dist = 0;
}

void	init_draw_data(t_game *game)
{
	game->draw = malloc(sizeof(t_draw_data));
	game->draw->color = 0;
	game->draw->draw_e = 0;
	game->draw->draw_s = 0;
	game->draw->line_h = 0;
	game->draw->step = 0;
	game->draw->tex_pos = 0;
	game->draw->tex_x = 0;
	game->draw->tex_y = 0;
	game->draw->wall_x = 0;
	game->draw->tex_h = 64;
	game->draw->tex_w = 64;
}

void	init_textures(t_game *game)
{
	game->tex = malloc(sizeof(t_textures));
	game->tex->ea = malloc(sizeof(t_data));
	game->tex->we = malloc(sizeof(t_data));
	game->tex->no = malloc(sizeof(t_data));
	game->tex->so = malloc(sizeof(t_data));
	game->tex->ea->addr = NULL;
	game->tex->we->addr = NULL;
	game->tex->no->addr = NULL;
	game->tex->so->addr = NULL;
}

void	init_keys(t_game *game)
{
	game->keys = malloc(sizeof(t_keyboard));
	game->keys->left_key = false;
	game->keys->right_key = false;
	game->keys->w_key = false;
	game->keys->s_key = false;
	game->keys->shift_key = false;
}

void	init_all(t_game *game)
{
	init_mlx(game);
	init_player_data(game);
	init_ray_data(game);
	init_draw_data(game);
	init_textures(game);
	init_keys(game);
}