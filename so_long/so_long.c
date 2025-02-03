/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:52:54 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/03 09:42:31 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Loads the map from a file and validates its structure.
 * @param game Pointer to the game state structure.
 * @param argv Command-line arguments containing the map file path.
 */
void	load_and_validate_map(t_game_state *game, char **argv)
{
	if (parse_map(game, argv) == 0)
	{
		ft_putstr_fd("Error\nPlease input a valid map\n", 2);
		free_game_resources(game);
		exit(1);
	}
}

/*
 * Frees all graphical assets (images) used by the game.
 * @param game Pointer to the game state structure.
 */
static void	free_images(t_game_state *game)
{
	if (!game || !game->img)
		return ;
	if (game->img->ground)
		mlx_delete_image(game->mlx, game->img->ground);
	if (game->img->ocean)
		mlx_delete_image(game->mlx, game->img->ocean);
	if (game->img->player)
		mlx_delete_image(game->mlx, game->img->player);
	if (game->img->exit)
		mlx_delete_image(game->mlx, game->img->exit);
	if (game->img->collectible)
		mlx_delete_image(game->mlx, game->img->collectible);
	free(game->img);
}

/*
 * Frees all dynamically allocated resources used by the game.
 * @param game Pointer to the game state structure.
 */
void	free_game_resources(t_game_state *game)
{
	int	i;

	if (!game)
		return ;
	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			if (game->map[i])
			{
				free(game->map[i]);
			}
			i++;
		}
		free(game->map);
	}
	if (game->img)
		free_images(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game)
		free(game);
}

/*
 * Initializes and runs the game loop.
 * @param argv Command-line arguments containing the map file path.
 */
void	run_game(char **argv)
{
	t_game_state	*game;

	game = malloc(sizeof(t_game_state));
	if (!game)
		exit(1);
	ft_bzero(game, sizeof(t_game_state));
	load_and_validate_map(game, argv);
	game->mlx = mlx_init(game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long", false);
	if (!game->mlx)
	{
		free_game_resources(game);
		exit(1);
	}
	load_textures(game);
	render_graphics(game);
	mlx_key_hook(game->mlx, move_player, game);
	mlx_loop(game->mlx);
	free_game_resources(game);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
	{
		ft_putstr_fd("Error\nPlease provide a file with a .ber extension.\n", 2);
		return (1);
	}
	run_game(argv);
	return (0);
}