/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:57:38 by fmorenil          #+#    #+#             */
/*   Updated: 2025/05/14 19:39:22 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static void	ft_free_cub(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->map)
	{
		while (cub->map->lines[i])
		{
			free(cub->map->lines[i]);
			i++;
		}
		free(cub->map->lines);
		free(cub->map);
	}
	ft_close_win((void *)cub);
}

static t_map	*ft_init_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	return (map);
}

static t_cub	*ft_init(char *str)
{
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->title = ft_strjoin("Cub3D - ", str);
	if (!cub)
		return (ft_print_error("Malloc error", NULL, 1), NULL);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_print_error("Connection error", NULL, 1), NULL);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, cub->title);
	if (!cub->win)
		return (ft_print_error("Window error", NULL, 1), NULL);
	cub->img = mlx_new_image(cub->mlx, 1920, 1080);
	if (!cub->img)
		return (ft_print_error("Image error", NULL, 1), NULL);
	cub->data_addr = mlx_get_data_addr(cub->img, &cub->bpp,
			&cub->size_line, &cub->endian);
	cub->map = ft_init_map();
	ft_init_movements(cub);
	ft_init_textures(cub);
	cub->floor_color = FLOOR_COLOR;
	cub->cell_color = CEILING_COLOR;
	return (cub);
}

static int	ft_check_args(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + (len - 4), ".cub", 4) || len <= 4)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		return (ft_print_error("Error: Incorrect number of args", NULL, 1));
	if (ft_check_args(argv[1]))
		return (ft_print_error("Error: Incorrect file extension:", argv[1], 1));
	cub = ft_init(argv[1]);
	if (ft_read_file(argv[1], cub, cub->map))
	{
		ft_free_cub(cub);
		return (1);
	}
	ft_controls(cub);
	mlx_loop_hook(cub->mlx, ft_draw, cub);
	mlx_loop(cub->mlx);
}
