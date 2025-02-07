/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:19:57 by mbyrne            #+#    #+#             */
/*   Updated: 2025/02/04 09:54:56 by mbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>

typedef struct s_pipex
{
	char	*file1;
	char	*cmd1;
	char	*cmd2;
	char	*file2;
	char	**path;
}	t_pipex;

int		handle_pipex(t_pipex *pipex, int *p_fd, char **env);
int		open_file(char *file, int in_or_out);
void	ft_free_array(char **tab);
void	exec_command(char *cmd, char **env);
char	*ft_get_env(const char *name, char **env);
char	*ft_get_path(char *cmd, char **env);
char	**ft_pipex_split_args(const char *input);

#endif