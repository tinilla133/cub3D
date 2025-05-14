/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:39:43 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/14 19:42:41 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_init_movements(t_cub *cub)
{
	cub->keys.forward = 0;
	cub->keys.backward = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
	cub->keys.rotate_left = 0;
	cub->keys.rotate_right = 0;
}

void	ft_init_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		cub->texture[i].img = NULL;
		cub->texture[i].data_addr = NULL;
		cub->texture[i].path = NULL;
		cub->texture[i].width = 0;
		cub->texture[i].height = 0;
		cub->texture[i].bpp = 0;
		cub->texture[i].size_line = 0;
		cub->texture[i].endian = 0;
		cub->texture[i].text_x = 0;
		cub->texture[i].text_y = 0;
		cub->texture[i].wall_x = 0;
		i++;
	}
}
