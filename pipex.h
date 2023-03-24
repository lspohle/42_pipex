/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:46:16 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/24 08:37:15 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define CYAN "\e[38;5;51m"
# define GREEN "\e[38;5;47m"
# define PURPLE "\e[38;5;219m"
# define RED "\e[38;5;196m"
# define ESC "\033[0m"

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe_fd[2];
	int		file_fd[2];
	pid_t	pipe_id;
	char	**env_paths;
}				t_data;

void	exit_cmd_failed(char *cmd);
void	exit_open_failed(char *str, int fd);
void	exit_cmd_not_found(char *cmd);
void	process_parent(t_data pipex);
void	process_child(t_data pipex);

char	**check_for_special(char *cmd);
int	count_quotes(int *i, char *str);

#endif