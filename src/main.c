/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:09:01 by rtosun            #+#    #+#             */
/*   Updated: 2022/10/01 16:36:18 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double posX = 3, posY = 3;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 3.14159 / 4.0;
float rotSpeed = 0.5f;
int texWidth = 64;
int texHeight = 64;

int	key_events(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->window);
		exit(0);
	}
	if (keycode == 0)
	{
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	if (keycode == 2)
	{
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if (keycode == 13)
	{
		if(map[(int)(posX + dirX * 0.5f)][(int)posY] == 0) 
			posX += dirX * 0.5f;
		if(map[(int)posX][(int)(posY + dirY * 0.5f)] == 0)
			posY += dirY * 0.5f;
	}
	if (keycode == 1)
	{
		if(map[(int)(posX - dirX * 0.5f)][(int)posY] == 0)
			posX -= dirX * 0.5f;
		if(map[(int)(posX)][(int)(posY - dirY * 0.5f)] == 0)
			posY -= dirY * 0.5f;
	}
	if (keycode == 3)
		planeY -= 0.1;
	return (0);
}

void	init_all(t_game *game)
{
	int a;
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	game->image = malloc(sizeof(t_data));
	game->wall = malloc(sizeof(t_data));
	game->brick = malloc(sizeof(t_data));
	game->image->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->brick->img = mlx_xpm_file_to_image(game->mlx, "/Users/rtosun/Desktop/Cub3dd/sprites/brick.xpm", &a, &a);
	game->wall->img = mlx_xpm_file_to_image(game->mlx, "/Users/rtosun/Desktop/Cub3dd/sprites/eagle.xpm", &a, &a);
	game->wall->addr = (int *)mlx_get_data_addr(game->wall->img, &game->wall->bits_per_pixel, &game->wall->line_length, &game->wall->endian);
	game->image->addr = (int *)mlx_get_data_addr(game->image->img, &game->image->bits_per_pixel, &game->image->line_length, &game->image->endian);
	game->brick->addr = (int *)mlx_get_data_addr(game->brick->img, &game->brick->bits_per_pixel, &game->brick->line_length, &game->brick->endian);
}

int	update(t_game *game)
{
	for(int x = 0; x < screenWidth; x++)
	{
		//ışın konumunu ve yönünü hesaplama
		double cameraX = 2 * x / (double)screenWidth - 1; //kamera uzayında x koordinatı
		// ray'in gideceği açıyı hesaplamak için kamera düzlemini buluyoruz -1'den başlayarak 1'e kadar gidiyor bunu ekranın büyüklüğüne göre sistematik olarak işliyor.
		double rayDirX = dirX + (planeX * cameraX);
		double rayDirY = dirY + (planeY * cameraX);
		//haritanın hangi kutusundayız

		int mapX = (int)posX;
		int mapY = (int)posY;
		//mevcut konumdan sonraki x veya y tarafına kadar olan ışının uzunluğu
		double sideDistX;
		double sideDistY;
		//bir x veya y tarafından bir sonraki x veya y tarafına kadar olan ışının uzunluğu
		//bunlar türetilmiştir:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		//abs(|rayDir| / rayDirX) ve abs(|rayDir| / rayDirY) olarak basitleştirilebilir
		//böylelikle |rayDir| vektörün uzunluğudur (rayDirX, rayDirY). Uzunluğu, 
		//(dirX, dirY)'den farklı olarak 1 değildir, ancak bunun bir önemi yoktur, 
		//DDA'nın aşağıda daha ileri adım atma şekli nedeniyle yalnızca deltaDistX ve 
		//deltaDistY arasındaki oran önemlidir. Yani değerler aşağıdaki gibi hesaplanabilir.
		// IEEE 754 kayan nokta değerleri ile C++'da teknik olarak buna gerek olmamasına rağmen sıfıra bölme engellenir.
		double deltaDistX;
		if (rayDirX == 0) 
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		double deltaDistY; 
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		//x veya y yönünde hangi yönde adım atılacağı bulunur(+1 veya -1)
		int stepX;
		int stepY;
		bool hit;
		
		hit = false; //ray'in duvara carpip carpmadigini kontrol eder.
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while(!hit)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(map[mapX][mapY] > 0)
				hit = true;
		}

		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on scree
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) 
			drawStart = 0;
		if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		//int texNum = map[mapX][mapY] - 1;
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;		
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;

		//choose wall color
		//give x and y sides different brightness
		//draw the pixels of the stripe as a vertical line
		// for (int i = 0; i < drawStart; i++)
			// game->image->addr[i * screenWidth + x] = 0x33ffff;
		for (int y = 0; y < screenHeight; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			unsigned int color;
			if (y < drawStart)
				color = 0x33ffff;
			else if (y > drawEnd)
				color = 0x17F662;
			else
			{
				if (side == 0)
					color = game->wall->addr[texHeight * texY + texX];
				else
					color = game->brick->addr[texHeight * texY + texX];
				texPos += step;
			}
			game->image->addr[y * screenWidth + x] = color;
		}
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image->img, 0, 0);
}

int main()
{
	t_game game;

	init_all(&game);
	mlx_hook(game.window,2, 1L<<0, key_events, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_loop(game.mlx);
	return (31);
}