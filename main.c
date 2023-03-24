/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/24 08:34:19 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	print_arr(char **arr)
// {
// 	int i;
	
// 	i = -1;
// 	while (arr[++i] != NULL)
// 		ft_printf(GREEN"Arr[%i]: %s\n"ESC, i, arr[i]);
// 	ft_printf(GREEN"Arr[%i]: %s\n"ESC, i, arr[i]);
// }

static int	ft_pipex(t_data pipex)
{
	if (pipe(pipex.pipe_fd) == -1)
		exit_cmd_failed("pipe");
	pipex.pipe_id = fork();
	if (pipex.pipe_id == -1)
		exit_cmd_failed("fork");
	if (pipex.pipe_id == 0)
		process_child(pipex);
	waitpid(pipex.pipe_id, NULL, WNOHANG);
	if (pipex.pipe_id > 0)
		process_parent(pipex);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;
	
	if (argc != 5)
		exit_cmd_failed("Invalid number of arguments");
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.file_fd[1] = open(pipex.argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.file_fd[1] == -1)
		exit_open_failed(pipex.argv[4], -1);
	pipex.file_fd[0] = open(pipex.argv[1], O_RDONLY);
	if (pipex.file_fd[0] == -1)
		exit_open_failed(pipex.argv[1], pipex.file_fd[1]);
	ft_pipex(pipex);
	close(pipex.file_fd[0]);
	close(pipex.file_fd[1]);
	return (0);
}
