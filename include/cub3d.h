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

# define screenWidth 480
# define screenHeight 360

typedef struct	s_data {
	void	*img;
	int		*addr;
}				t_data;

typedef struct s_Player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	float	rot_speed;
	float	speed;
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

typedef struct s_keyboard
{
	bool	left_key;
	bool	right_key;
	bool	w_key;
	bool	s_key;
	bool	a_key;
	bool	d_key;
	bool	shift_key;
}	t_keyboard;

typedef struct s_minimap
{
	int	x;
	int	y;
	int	py;
	int	px;
	int	i;
}	t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_data		*image;
	t_player	*pdata;
	t_ray		*ray;
	t_draw_data	*draw;
	t_textures	*tex;
	t_keyboard	*keys;
	t_minimap	*minimap;
	char		**map;
}	t_game;


int		ft_atoi_base(const char *str);
void	init_all(t_game *game);
int		key_press(int keycode, t_game *game);
int		update(t_game *game);
void	hit_check(t_game *game, int *side, int stepx, int stepy);
void	calculate_textures(t_game *game, int side);
void	calculate_pixels(t_game *game);
void	calculate_steps(t_game *game, int *step_x, int *step_y);
void	calculate_ray(t_game *game, int x);
int		key_release(int keycode, t_game *game);
void	movements(t_game *game);
char	*ft_str_join(char *left_str, char *buff);
void	free_2d_array(char **ptr);
int		no_blank_len(char **str);
int		find_double_array_len(char **s);
bool	check_map(t_game *game, char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		get_color(char *str);
void	init_keys(t_game *game);
void	init_textures(t_game *game);
void	init_minimap(t_game *game);
void	minimap(t_game *game);
void	free_all(t_game *game);
void	go_east(t_game *game);
void	go_west(t_game *game);
void	go_north(t_game *game);
void	go_south(t_game *game);
void	rotate_right(t_player *p);
int		check_map_surrounded(t_game *game);
void	ft_exit(char *str);
int	len_2d_into(char **s);

#endif
