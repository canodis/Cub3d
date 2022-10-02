#include "../include/cub3d.h"

//calculate lowest and highest pixel to fill in current stripe

void	draw_vertical(t_game *game, int x, int side)
{
	int	y;

	y = -1;
	while (++y < screenHeight)
	{
		game->draw->tex_y = (int)game->draw->tex_pos & (game->draw->tex_h - 1);
		if (y < game->draw->draw_s)
			game->draw->color = 0x33ffff;
		else if (y > game->draw->draw_e)
			game->draw->color = 0x17F662;
		else
		{
			if (side == 0)
				game->draw->color = game->tex->ea->addr[game->draw->tex_h * game->draw->tex_y + game->draw->tex_x];
			else
				game->draw->color = game->tex->so->addr[game->draw->tex_h * game->draw->tex_y + game->draw->tex_x];
			game->draw->tex_pos += game->draw->step;
		}
			game->image->addr[y * screenWidth + x] = game->draw->color;
	}
}

int	update(t_game *game)
{
	int		x;
	int		stepX;
	int		stepY;
	int		side;

	x = -1;
	while(++x < screenWidth)
	{
		calculate_ray(game, x);
		calculate_steps(game, &stepX, &stepY);
		hit_check(game, &side, stepX, stepY);
		calculate_pixels(game);
		//double wall_x; //where exactly the wall was hit
		if (side == 0)
			game->draw->wall_x = game->pdata->pos_y + game->ray->wall_dist * game->ray->ray_diry;
		else
			game->draw->wall_x = game->pdata->pos_x + game->ray->wall_dist * game->ray->ray_dirx;
		game->draw->wall_x -= floor((game->draw->wall_x));
		calculate_textures(game, side);
		draw_vertical(game, x, side);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);
	return (0);
}