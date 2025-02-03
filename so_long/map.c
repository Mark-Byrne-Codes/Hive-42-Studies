/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:29:48 by mbyrne            #+#    #+#             */
/*   Updated: 2025/01/31 10:05:38 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Adds a new line to the game map, reallocating memory as needed.
 * Frees the old map and updates the game state with the new map.
 * 
 * @param game Pointer to the game state structure.
 * @param line The new line to add to the map.
 * @return     1 on success, 0 on failure (e.g., memory allocation error).
 */
static int	next_line(t_game_state *game, char *line)
{
	char	**temp;
	int		i;

	if (!line)
		return (0);
	i = 0;
	game->map_height++;
	temp = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!temp)
	{
		free(line);
		return (0);
	}
	temp[game->map_height] = NULL;
	while (i < game->map_height - 1)
	{
		temp[i] = game->map[i];
		i++;
	}
	temp[i] = line;
	if (game->map)
		free(game->map);
	game->map = temp;
	return (1);
}

/*
 * Checks if a tile is valid and updates the game state counters.
 * Increments collectibles, sets player position,
 * or increments exits based on the tile type.
 * 
 * @param game Pointer to the game state structure.
 * @param tile The tile character to check.
 * @param row  The row (Y-coordinate) of the tile.
 * @param col  The column (X-coordinate) of the tile.
 * @return     1 if the tile is valid, 0 if the tile is invalid.
 */
static int	check_tile(t_game_state *game, char tile, int row, int col)
{
	if (tile == 'C')
		game->collectibles++;
	else if (tile == 'P')
	{
		game->player_x = col;
		game->player_y = row;
		game->player_count++;
	}
	else if (tile == 'E')
		game->exits++;
	else if (tile != '1' && tile != '0' && tile != '\n')
		return (0);
	return (1);
}

/*
 * Validates the map structure and contents, 
 *	ensuring proper boundaries and tile validity.
 * Checks that the map is surrounded by walls, 
 * contains exactly one player, at least one collectible, and exactly one exit.
 * 
 * @param game Pointer to the game state structure.
 * @return     1 if the map is valid, 0 otherwise.
 */
static int	validate_map(t_game_state *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			if ((row == 0 || row == game->map_height - 1 || \
				col == 0 || col == game->map_width - 1)
				&& game->map[row][col] != '1')
				return (0);
			if (!check_tile(game, game->map[row][col], row, col))
				return (0);
			col++;
		}
		row++;
	}
	return (game->player_count == 1 && \
		game->collectibles > 0 && game->exits == 1);
}

/*
 * Validates the map structure and checks if a valid path exists.
 * @param game Pointer to the game state structure.
 * @param params Flood-fill parameters for path validation.
 * @return 1 if the map is valid and has a valid path and fits the screen, 
 * 0 otherwise.
 */
int	validate_and_check_path(t_game_state *game, t_flood_fill_params params)
{
	game->map_width = ft_strlen(game->map[0]);
	if (game->map[0][game->map_width - 1] == '\n')
		game->map_width--;
	game->map_height = 0;
	while (game->map[game->map_height])
		game->map_height++;
	if (game->map_width > MAX_MAP_WIDTH || game->map_height > MAX_MAP_HEIGHT)
		return (0);
	if (!validate_map(game))
		return (0);
	if (!check_map_path(game, params))
		return (0);
	return (1);
}

/*
 * Parses the map file and initializes the game's map data.
 * @param game Pointer to the game state structure.
 * @param argv Command-line arguments containing the map file path.
 * @return 1 on success, 0 on failure.
 */
int	parse_map(t_game_state *game, char **argv)
{
	t_flood_fill_params	params;
	int					fd;
	char				*readmap;
	int					has_content;

	ft_bzero(&params, sizeof(t_flood_fill_params));
	fd = open(argv[1], O_RDONLY);
	has_content = 0;
	if (fd < 0)
		return (0);
	while (1)
	{
		readmap = get_next_line(fd);
		if (!readmap)
			break ;
		has_content = 1;
		if (!next_line(game, readmap))
			break ;
	}
	close(fd);
	if (!has_content || !game->map || !game->map[0])
		return (0);
	return (validate_and_check_path(game, params));
}