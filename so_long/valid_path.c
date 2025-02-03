/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:19:16 by mbyrne            #+#    #+#             */
/*   Updated: 2025/01/26 13:25:48 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Recursively explores the map using the flood-fill algorithm 
 * to mark reachable cells.
 * Decrements the collectible count if a collectible is found 
 * and marks the exit as found.
 * Marks visited cells with 'x' to prevent reprocessing.
 * 
 * @param params Pointer to the flood-fill parameters structure.
 * @param y      The current row (Y-coordinate) being processed.
 * @param x      The current column (X-coordinate) being processed.
 */
void	flood_fill(t_flood_fill_params *params, int y, int x)
{
	if (x < 0 || x >= params->map_width || y < 0 || y >= params->map_height
		|| params->map[y][x] == '1' || params->map[y][x] == 'x')
		return ;
	if (params->map[y][x] == 'C')
		(*params->collectibles)--;
	if (params->map[y][x] == 'E')
		*params->exit_found = 1;
	params->map[y][x] = 'x';
	flood_fill(params, y + 1, x);
	flood_fill(params, y, x + 1);
	flood_fill(params, y - 1, x);
	flood_fill(params, y, x - 1);
}

/*
 * Frees a dynamically allocated 2D array representing a map copy.
 * 
 * @param map_copy    The 2D array to be freed.
 * @param map_height  The height of the map (number of rows).
 */
static void	free_map_copy(char **map_copy, int map_height)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (i < map_height)
	{
		if (map_copy[i])
			free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

/*
 * Checks if all exits and collectibles in the map copy have been reached.
 * 
 * @param game      Pointer to the game state structure.
 * @param map_copy  The 2D array representing the map copy.
 * @return          1 if all exits and collectibles are reachable, 0 otherwise.
 */
static int	check_for_valid_game(t_game_state *game, char **map_copy)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{	
			if (map_copy[i][j] == 'E' || map_copy[i][j] == 'C')
				found++;
			j++;
		}
		i++;
	}
	return (found == 0);
}

/*
 * Creates a copy of the game map.
 * 
 * @param map         The original 2D array representing the map.
 * @param map_height  The height of the map (number of rows).
 * @return            A pointer to the newly allocated map copy, or NULL.
 */
static char	**copy_map(char **map, int map_height)
{
	int		i;
	char	**map_copy;

	map_copy = malloc(map_height * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < map_height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			free_map_copy(map_copy, i);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

/*
 * Checks if there is a valid path from the player 
 * to all collectibles and the exit.
 * @param game Pointer to the game state structure.
 * @param params Flood-fill parameters for path validation.
 * @return 1 if a valid path exists, 0 otherwise.
 */
int	check_map_path(t_game_state *game, t_flood_fill_params params)
{
	int		collectibles;
	int		exit_found;
	int		player_x;
	int		player_y;
	char	**map_copy;

	collectibles = game->collectibles;
	exit_found = 0;
	map_copy = copy_map(game->map, game->map_height);
	if (!map_copy)
		return (0);
	params.map = map_copy;
	params.map_width = game->map_width;
	params.map_height = game->map_height;
	params.collectibles = &collectibles;
	params.exit_found = &exit_found;
	player_x = game->player_x;
	player_y = game->player_y;
	flood_fill(&params, player_y, player_x);
	if (!check_for_valid_game(game, map_copy))
		exit_found = 0;
	free_map_copy(map_copy, game->map_height);
	return (collectibles == 0 && exit_found);
}