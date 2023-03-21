/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/21 13:40:39 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_error(int errnum)
{
	ft_printf(RED"Error: "ESC"%s\n", strerror(errnum));
	exit (1);
}

int	ft_pipex(t_data pipex)
{
	if (pipe(pipex.pipe_fd) == -1)
		display_error(errno);
	pipex.pipe_id = fork();
	if (pipex.pipe_id == -1)
		display_error(errno);
	if (pipex.pipe_id == 0)
		process_child(pipex);
	else
		process_parent(pipex);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;

	if (argc != 5)
		display_error(EINVAL);
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.file_fd[0] = open(pipex.argv[1], O_RDONLY);
	if (pipex.file_fd[0] == -1)
		display_error(errno);
	pipex.file_fd[1] = open(pipex.argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.file_fd[1] == -1)
		display_error(errno);
	ft_pipex(pipex);
	while (*pipex.env_paths != NULL)
		free (*pipex.env_paths);
	free (*pipex.env_paths);
	close(pipex.file_fd[0]);
	close(pipex.file_fd[1]);
	return (0);
}
