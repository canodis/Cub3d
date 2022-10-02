#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"

# define screenWidth 1920
# define screenHeight 1080
# define mapWidth 24
# define mapHeight 24

extern int map[mapWidth][mapHeight];

typedef struct	s_data {
	void	*img;
	int		*addr;
}				t_data;

typedef struct s_Player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	float rot_speed;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dirx;
	double	ray_diry;
	int		mapx;
	int		mapy;
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	double	wall_dist;
}	t_ray;

typedef struct s_draw_data
{
	int				draw_s;
	int				draw_e;
	int				line_h;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned int	color;
	int				tex_w;
	int				tex_h;
}	t_draw_data;

typedef struct s_textures
{
	t_data			*no;
	t_data			*so;
	t_data			*we;
	t_data			*ea;
	unsigned int	floorc;
	unsigned int	ceilingc;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_data		*image;
	t_player	*pdata;
	t_ray		*ray;
	t_draw_data	*draw;
	t_textures	*tex;
}	t_game;



void	init_all(t_game *game);
int		key_events(int keycode, t_game *game);
int		update(t_game *game);
void	hit_check(t_game *game, int *side, int stepx, int stepy);
void	calculate_textures(t_game *game, int side);
void	calculate_pixels(t_game *game);
void	calculate_steps(t_game *game, int *step_x, int *step_y);
void	calculate_ray(t_game *game, int x);

#endif