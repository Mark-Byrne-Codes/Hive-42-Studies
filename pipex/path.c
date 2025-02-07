/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:52:15 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/04 10:14:31 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Frees the memory allocated for an array of strings.
**
** @param tab: Array of strings to be freed
*/
void	ft_free_array(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
** Opens the specified file for reading or writing.
** If in_or_out is 0, opens the file in read-only mode.
** If in_or_out is 1, opens the file in write-only mode, creates it if necessary,
** and truncates it if it already exists.
** Exits with an error message if the file cannot be opened.
**
** @param file:      The name of the file to open
** @param in_or_out: Mode to open the file (0 for read, 1 for write)
** @return:          File descriptor of the opened file, or -1 on error
*/
int	open_file(char *file, int in_or_out)
{
	int	ret;

	ret = -1;
	if (in_or_out == 0)
	{
		ret = open(file, O_RDONLY);
		if (ret == -1)
			perror(file);
	}
	else if (in_or_out == 1)
	{
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ret == -1)
			perror(file);
	}
	return (ret);
}

/*
** Retrieves the value of an environment variable.
** Searches the environment array for a variable matching the specified name.
** Returns the value of the variable if found, or NULL if not found.
**
** @param name: The name of the environment variable to retrieve
** @param env:  The environment variables array
** @return:     The value of the environment variable, or NULL if not found
*/
char	*ft_get_env(const char *name, char **env)
{
	int		i;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

/*
** Combines a directory and a command to form an executable path.
** Checks if the resulting path points to an executable file.
** Returns the full path if executable, or NULL otherwise.
**
** @param dir: The directory part of the path
** @param cmd: The command to append to the directory
** @return:    The full path to the executable, or NULL if not executable
*/
static char	*check_path(char *dir, char *cmd)
{
	char	*path_part;
	char	*exec;

	path_part = ft_strjoin(dir, "/");
	if (!path_part)
		return (NULL);
	exec = ft_strjoin(path_part, cmd);
	free(path_part);
	if (exec && access(exec, F_OK | X_OK) == 0)
		return (exec);
	free(exec);
	return (NULL);
}

/*
** Resolves the full path of a command by searching the directories in the PATH.
** Splits the PATH environment variable into directories 
** and checks each directory
** for an executable file matching the command name.
** Returns the full path to the executable if found, or NULL otherwise.
**
** @param cmd: The command to find the path for
** @param env: The environment variables array
** @return:    The full path to the executable, or NULL if not found
*/
char	*ft_get_path(char *command, char **env)
{
	char	**directories;
	char	*full_path;
	int		i;

	if (!command || !*command)
		return (NULL);
	directories = ft_split(ft_get_env("PATH", env), ':');
	if (!directories)
		return (NULL);
	i = 0;
	while (directories[i])
	{
		full_path = check_path(directories[i], command);
		if (full_path)
		{
			ft_free_array(directories);
			return (full_path);
		}
		i++;
	}
	ft_free_array(directories);
	return (NULL);
}