/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:48:42 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/03 09:46:57 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Handles the player reaching the exit at the specified coordinates.
 * @param game Pointer to the game state structure.
 * @param new_x X-coordinate of the exit.
 * @param new_y Y-coordinate of the exit.
 */
void	handle_exit(t_game_state *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E')
	{
		if (game->collected == game->collectibles)
		{
			ft_printf("All Wood gathered! Set Sail!\n");
			free_game_resources(game);
			exit(0);
		}
	}
}

/*
 * Handles the collection of a collectible item at the specified coordinates.
 * @param game Pointer to the game state structure.
 * @param new_x X-coordinate of the collectible.
 * @param new_y Y-coordinate of the collectible.
 */
void	handle_collectible(t_game_state *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map[new_y][new_x] = '0';
		mlx_image_to_window(game->mlx, game->img->ground,
			new_x * TILE_SIZE, new_y * TILE_SIZE);
	}
}

/*
 * Handles the ESC key press to exit the game.
 * @param keydata MLX42 key data structure containing key press information.
 * @param game Pointer to the game state structure.
 */
void	handle_esc(mlx_key_data_t keydata, t_game_state *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("Exiting game...\n");
		free_game_resources(game);
		exit(0);
	}
}

/*
 * Updates the player's position on the map and handles movement logic.
 * @param game Pointer to the game state structure.
 * @param new_x New X-coordinate for the player.
 * @param new_y New Y-coordinate for the player.
 */
void	update_player_position(t_game_state *game, int new_x, int new_y)
{
	if (new_y < 0 || new_y >= game->map_height || new_x < 0 || \
		new_x >= game->map_width || \
		game->map[new_y][new_x] == '1' || \
		(game->map[new_y][new_x] == 'E' && \
		game->collected < game->collectibles) || \
		(new_x == game->player_x && new_y == game->player_y))
	{
		return ;
	}
	mlx_image_to_window(game->mlx, game->img->ground,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves count: %d\n", game->moves);
	mlx_image_to_window(game->mlx, game->img->player,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}

/*
 * Handles player movement based on key input.
 * @param keydata MLX42 key data structure containing key press information.
 * @param param Pointer to the game state structure.
 */
void	move_player(mlx_key_data_t keydata, void *param)
{
	t_game_state	*game;
	int				new_x;
	int				new_y;

	game = (t_game_state *)param;
	handle_esc(keydata, game);
	if (keydata.action == MLX_PRESS)
	{
		new_x = game->player_x;
		new_y = game->player_y;
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			new_y--;
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			new_y++;
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			new_x--;
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			new_x++;
		handle_collectible(game, new_x, new_y);
		handle_exit(game, new_x, new_y);
		update_player_position(game, new_x, new_y);
	}
}