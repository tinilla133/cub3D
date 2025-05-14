/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:56:33 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/14 19:41:27 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = cub->data_addr + (y * cub->size_line + x * (cub->bpp / 8));
	*(unsigned int *)dst = color;
}

int	ft_update_player(t_cub *cub)
{
	if (cub->keys.forward)
		ft_move_player(cub, FORWARD);
	if (cub->keys.backward)
		ft_move_player(cub, BACKWARD);
	if (cub->keys.left)
		ft_move_player(cub, LEFT);
	if (cub->keys.right)
		ft_move_player(cub, RIGHT);
	if (cub->keys.rotate_left)
		ft_rotate_player(cub, LEFT);
	if (cub->keys.rotate_right)
		ft_rotate_player(cub, RIGHT);
	return (0);
}

int	ft_check_lines(char	**lines)
{
	int	i;
	int	character;

	i = 0;
	character = 0;
	while (lines[i])
	{
		if (!ft_check_characters(lines[i], &character))
			return (ft_print_error("Error: Map characters", NULL, 0));
		i++;
	}
	if (character == 0)
		return (ft_print_error("Error: No position for player!", NULL, 0));
	if (character > 1)
		return (ft_print_error("Error: Multiple players!", NULL, 0));
	return (1);
}

void	ft_find_player(char **lines, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == 'N' || lines[i][j] == 'S'
				|| lines[i][j] == 'E' || lines[i][j] == 'W')
			{
				player->orientation = lines[i][j];
				player->x_coord = j + 0.5;
				player->y_coord = i + 0.5;
				lines[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_player(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->x_direction = 0;
		player->y_direction = -1;
	}
	else if (player->orientation == 'S')
	{
		player->x_direction = 0;
		player->y_direction = 1;
	}
	else if (player->orientation == 'E')
	{
		player->x_direction = 1;
		player->y_direction = 0;
	}
	else if (player->orientation == 'W')
	{
		player->x_direction = -1;
		player->y_direction = 0;
	}
	player->x_plane = -player->y_direction * 0.66;
	player->y_plane = player->x_direction * 0.66;
}
