/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:52:57 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/03 09:44:16 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "./MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>

# define TILE_SIZE 64
# define MAX_MAP_WIDTH 60
# define MAX_MAP_HEIGHT 33

typedef struct s_graphics
{
	mlx_image_t	*ground;
	mlx_image_t	*ocean;
	mlx_image_t	*player;
	mlx_image_t	*exit;
	mlx_image_t	*collectible;
}	t_graphics;

typedef struct s_game_state
{
	t_graphics	*img;
	mlx_t		*mlx;
	int			player_x;
	int			player_y;
	int			player_count;
	int			collectibles;
	int			collected;
	int			moves;
	int			exits;
	int			map_width;
	int			map_height;
	char		**map;
}	t_game_state;

typedef struct s_flood_fill_params
{
	int		map_width;
	int		map_height;
	int		*collectibles;
	int		*exit_found;
	char	**map;
}	t_flood_fill_params;

int		parse_map(t_game_state *game, char **argv);
int		check_map_path(t_game_state *game, t_flood_fill_params params);
int		validate_and_check_path(t_game_state *game, t_flood_fill_params params);
void	run_game(char **argv);
void	free_game_resources(t_game_state *game);
void	load_and_validate_map(t_game_state *game, char **argv);
void	render_graphics(t_game_state *game);
void	load_textures(t_game_state *game);
void	handle_collectible(t_game_state *game, int new_x, int new_y);
void	handle_exit(t_game_state *game, int new_x, int new_y);
void	move_player(mlx_key_data_t keydata, void *param);

#endif