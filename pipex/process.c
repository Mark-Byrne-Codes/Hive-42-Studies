/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:27:47 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/06 09:31:52 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Executes the first command in the pipeline.
** Opens the input file, redirects input/output as required,
** and executes the command.
**
** @param pipex: Pointer to the pipex structure
** @param p_fd:  Pipe file descriptors
** @param env:   Environment variables array
*/
static void	first_child_process(t_pipex *pipex, int *p_fd, char **env)
{
	int	fd_in;

	fd_in = open_file(pipex->file1, 0);
	if (fd_in == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		exit(1);
	}
	dup2(fd_in, 0);
	dup2(p_fd[1], 1);
	close(fd_in);
	close(p_fd[0]);
	close(p_fd[1]);
	exec_command(pipex->cmd1, env);
}

/*
** Executes the second command in the pipeline.
** Opens the output file, redirects input/output as required,
** and executes the command.
**
** @param pipex: Pointer to the pipex structure
** @param p_fd:  Pipe file descriptors
** @param env:   Environment variables array
*/
static void	second_child_process(t_pipex *pipex, int *p_fd, char **env)
{
	int	fd_out;

	fd_out = open_file(pipex->file2, 1);
	if (fd_out == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		exit(1);
	}
	dup2(fd_out, 1);
	dup2(p_fd[0], 0);
	close(fd_out);
	close(p_fd[0]);
	close(p_fd[1]);
	exec_command(pipex->cmd2, env);
}

/*
** Handles the creation of a child process.
** If the process is successfully created, 
** it calls the provided process function.
**
** @param pid:    Pointer to the process ID
** @param process: Function to be executed in the child process
** @param pipex:  Pointer to the pipex structure
** @param p_fd:   Pipe file descriptors
** @param env:    Environment variables array
*/
static void	create_process(pid_t *pid,
	void (*process)(t_pipex *, int *, char **),
	t_pipex *pipex, int *p_fd, char **env)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (*pid == 0)
		process(pipex, p_fd, env);
}

/*
** Executes a command by finding its path and using execve.
** If the command is empty or not found, it prints an error and exits.
**
** @param cmd: Command to be executed
** @param env: Environment variables array
*/
void	exec_command(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !*cmd)
	{
		ft_putstr_fd("pipex: Command is empty\n", STDERR_FILENO);
		exit(127);
	}
	s_cmd = ft_pipex_split_args(cmd);
	if (!s_cmd || !s_cmd[0])
	{
		ft_putstr_fd("pipex: command not found\n", STDERR_FILENO);
		ft_free_array(s_cmd);
		exit(127);
	}
	path = ft_get_path(s_cmd[0], env);
	if (!path || execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found\n", STDERR_FILENO);
		ft_putendl_fd(s_cmd[0], STDERR_FILENO);
		ft_free_array(s_cmd);
		free(path);
		exit(127);
	}
}

/*
** Handles the creation of processes and waits for their completion.
** Returns the appropriate exit status based on the last command.
**
** @param pipex: Pointer to the pipex structure
** @param p_fd:  Pipe file descriptors
** @param env:   Environment variables array
** @return:      Exit status of the last command or 1 on error
*/
int	handle_pipex(t_pipex *pipex, int *p_fd, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	create_process(&pid1, first_child_process, pipex, p_fd, env);
	create_process(&pid2, second_child_process, pipex, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}