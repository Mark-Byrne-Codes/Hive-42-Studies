/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:12:16 by mbyrne            #+#    #+#             */
/*   Updated: 2025/01/27 12:13:25 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Places the player image on the game window at the specified row and column.
 * Updates the player's position in the game state.
 * 
 * @param game Pointer to the game state structure.
 * @param row  The row (Y-coordinate) where the player should be placed.
 * @param col  The column (X-coordinate) where the player should be placed.
 */
static void	place_player(t_game_state *game, int row, int col)
{
	mlx_image_to_window(game->mlx, game->img->player,
		col * TILE_SIZE, row * TILE_SIZE);
	game->player_x = col;
	game->player_y = row;
}

/*
 * Places a collectible image on the game window at the specified row and column.
 * 
 * @param game Pointer to the game state structure.
 * @param row  The row (Y-coordinate) where the collectible should be placed.
 * @param col  The column (X-coordinate) where the collectible should be placed.
 */
static void	place_collectible(t_game_state *game, int row, int col)
{
	mlx_image_to_window(game->mlx, game->img->collectible,
		col * TILE_SIZE, row * TILE_SIZE);
}

/*
 * Loads an image from a file, converts it to an MLX image, 
 *	and resizes it to the tile size.
 * Exits the game and frees resources if the image fails to load or convert.
 * 
 * @param game Pointer to the game state structure.
 * @param path The file path to the image.
 * @return     A pointer to the loaded and resized MLX image.
 */
static mlx_image_t	*load_image(t_game_state *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
	{
		free_game_resources(game);
		exit(1);
	}
	image = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
	{
		free_game_resources(game);
		exit(1);
	}
	mlx_resize_image(image, TILE_SIZE, TILE_SIZE);
	return (image);
}

/*
 * Loads all graphical assets (images) required for the game.
 * @param game Pointer to the game state structure.
 */
void	load_textures(t_game_state *game)
{
	game->img = malloc(sizeof(t_graphics));
	if (!game->img)
	{
		free_game_resources(game);
		exit(1);
	}
	game->img->ground = load_image(game, "./textures/ground.png");
	game->img->ocean = load_image(game, "./textures/ocean.png");
	game->img->exit = load_image(game, "./textures/exit.png");
	game->img->collectible = load_image(game, "./textures/collectible.png");
	game->img->player = load_image(game, "./textures/player.png");
}

/*
 * Renders the game map and all entities (player, collectibles, exit, etc.).
 * @param game Pointer to the game state structure.
 */
void	render_graphics(t_game_state *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			mlx_image_to_window(game->mlx, game->img->ground,
				col * TILE_SIZE, row * TILE_SIZE);
			if (game->map[row][col] == 'P')
				place_player(game, row, col);
			else if (game->map[row][col] == 'C')
				place_collectible(game, row, col);
			else if (game->map[row][col] == '1')
				mlx_image_to_window(game->mlx, game->img->ocean,
					col * TILE_SIZE, row * TILE_SIZE);
			else if (game->map[row][col] == 'E')
				mlx_image_to_window(game->mlx, game->img->exit,
					col * TILE_SIZE, row * TILE_SIZE);
			col++;
		}
		row++;
	}
}