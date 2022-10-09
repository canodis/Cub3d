#include "../include/cub3d.h"
void	calculate_ray(t_game *game, int x)
{
	//x veya y yönünde hangi yönde adım atılacağı bulunur(+1 veya -1)
	game->ray->camera_x = 2 * x / (double)screenWidth - 1;
	// ray'in gideceği açıyı hesaplamak için kamera düzlemini buluyoruz -1'den başlayarak 1'e kadar gidiyor bunu ekranın büyüklüğüne göre sistematik olarak işliyor.
	game->ray->ray_dirx = game->pdata->dir_x + (game->pdata->plane_x * game->ray->camera_x);
	game->ray->ray_diry = game->pdata->dir_y + (game->pdata->plane_y * game->ray->camera_x);
	// printf("plane x : %f     camera_x : %f      ray_dirx : %f         ray_diry : %f       \n", game->pdata->plane_x, game->ray->camera_x, game->ray->ray_dirx, game->ray->ray_diry);
	// ray_dirx = karakterin baktığı yöne göre açıyı hesaplar.
	// ray_diry = karakterin baktığı yöne göre açıyı hesaplar.
	//printf("\rdir_x : %f     dir_y : %f              ",game->ray->ray_dirx, game->ray->ray_diry);
	//haritanın hangi kutusundayız
	game->ray->mapx = (int)game->pdata->pos_x;
	game->ray->mapy = (int)game->pdata->pos_y;
	/* mevcut konumdan sonraki x veya y tarafına kadar olan ışının uzunluğu
	bir x veya y tarafından bir sonraki x veya y tarafına kadar olan ışının uzunluğu
	bunlar türetilmiştir:
	deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
	deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
	abs(|rayDir| / rayDirX) ve abs(|rayDir| / rayDirY) olarak basitleştirilebilir
	böylelikle |rayDir| vektörün uzunluğudur (rayDirX, rayDirY). Uzunluğu, 
	(dirX, dirY)'den farklı olarak 1 değildir, ancak bunun bir önemi yoktur, 
	DDA'nın aşağıda daha ileri adım atma şekli nedeniyle yalnızca deltaDistX ve 
	deltaDistY arasındaki oran önemlidir. Yani değerler aşağıdaki gibi hesaplanabilir.
	IEEE 754 kayan nokta değerleri ile C++'da teknik olarak buna gerek olmamasına rağmen sıfıra bölme engellenir.*/
	if (game->ray->ray_dirx == 0)
		game->ray->delta_distx = 1e30;
	else
		game->ray->delta_distx = fabs(1 / game->ray->ray_dirx);
	if (game->ray->ray_diry == 0)
		game->ray->delta_disty = 1e30;
	else
		game->ray->delta_disty = fabs(1 / game->ray->ray_diry);
}

//calculate step and initial sideDist
void	calculate_steps(t_game *game, int *step_x, int *step_y)
{
	if(game->ray->ray_dirx < 0)
	{
		*step_x = -1;
		game->ray->side_distx = (game->pdata->pos_x - game->ray->mapx) * game->ray->delta_distx;
	}
	else
	{
		*step_x = 1;
		game->ray->side_distx = (game->ray->mapx + 1.0 - game->pdata->pos_x) * game->ray->delta_distx;
	}
	if(game->ray->ray_diry < 0)
	{
		*step_y = -1;
		game->ray->side_disty = (game->pdata->pos_y - game->ray->mapy) * game->ray->delta_disty;
	}
	else
	{
		*step_y = 1;
		game->ray->side_disty = (game->ray->mapy + 1.0 - game->pdata->pos_y) * game->ray->delta_disty;
	}
}

void	calculate_pixels(t_game *game)
{
	game->draw->draw_s = -game->draw->line_h / 2 + screenHeight / 2;
	game->draw->draw_e = game->draw->line_h / 2 + screenHeight / 2;
	if(game->draw->draw_s < 0) 
		game->draw->draw_s = 0;
	if(game->draw->draw_e >= screenHeight)
		game->draw->draw_e = screenHeight - 1;
}

void	calculate_textures(t_game *game, int side)
{
	game->draw->tex_x = (int)(game->draw->wall_x * (double)game->draw->tex_w);
	if(side == 0 && game->ray->ray_dirx > 0)
		game->draw->tex_x = game->draw->tex_w - game->draw->tex_x - 1;
	if(side == 1 && game->ray->ray_diry < 0)
		game->draw->tex_x = game->draw->tex_w - game->draw->tex_x - 1;		
	game->draw->step = 1.0 * game->draw->tex_h / game->draw->line_h;
	// Starting texture coordinate
	game->draw->tex_pos = (game->draw->draw_s - screenHeight / 2 + game->draw->line_h / 2) * game->draw->step;
}

void	hit_check(t_game *game, int *side, int stepx, int stepy)
{
	char *str;
	while(1)
	{
		//side dist_x gönderilen ışının x düzlemindeki toplam uzunluğu
		//side dist_y gönderilen ışının y düzlemindeki toplam uzunluğu
		if(game->ray->side_distx < game->ray->side_disty)
		{
			game->ray->side_distx += game->ray->delta_distx;
			game->ray->mapx += stepx;
			*side = 0;
		}
		else
		{
			game->ray->side_disty += game->ray->delta_disty;
			game->ray->mapy += stepy;
			*side = 1;
		}
		//Check if ray has hit a wall
		if(game->map[game->ray->mapy][game->ray->mapx] == 49)
			break;
	}
		//printf("\rdelta_disty : %f                              ", game->ray->delta_disty);
/* 		Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		steps, but we subtract deltaDist once because one step more into the wall was taken above. */
	if(*side == 0)
		game->ray->wall_dist = (game->ray->side_distx - game->ray->delta_distx);
	else
		game->ray->wall_dist = (game->ray->side_disty - game->ray->delta_disty);
	game->draw->line_h = (int)(screenHeight / game->ray->wall_dist);
}