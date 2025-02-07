/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:20:00 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/06 08:43:03 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Main function: Entry point of the program.
** Validates argument count, initializes pipe, and starts process handling.
**
** @param argc: Argument count (must be 5)
** @param argv: Array of command line arguments
** @param env:  Environment variables array
** @return:     Exit status of the last command or 1 on error
*/
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		p_fd[2];
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	pipex.file1 = argv[1];
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	pipex.file2 = argv[4];
	if (pipe(p_fd) == -1)
	{
		perror("Pipe\n");
		return (1);
	}
	exit_status = handle_pipex(&pipex, p_fd, env);
	return (exit_status);
}