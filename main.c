/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/22 21:19:54 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_error(int exit_code)
{
	perror("Error");
	exit (exit_code);
}

void	error_msg(char *str, int fd)
{
	if (fd != -1)
		write(fd, "       0\n", 9);
	write(STDERR_FILENO, "pipex: ", 7);
	perror(str);
	exit(0);
}

int	ft_pipex(t_data pipex)
{
	if (pipe(pipex.pipe_fd) == -1)
		display_error(1);
	pipex.pipe_id = fork();
	if (pipex.pipe_id == -1)
		display_error(1);
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
		display_error(1);
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.file_fd[1] = open(pipex.argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.file_fd[1] == -1)
		error_msg(pipex.argv[4], -1);
	pipex.file_fd[0] = open(pipex.argv[1], O_RDONLY);
	if (pipex.file_fd[0] == -1)
		error_msg(pipex.argv[1], pipex.file_fd[1]);
	ft_pipex(pipex);
	// while (*pipex.env_paths != NULL)
	// 	free (*pipex.env_paths);
	// free (*pipex.env_paths);
	close(pipex.file_fd[0]);
	close(pipex.file_fd[1]);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	while (*argv != NULL && argc != 0)
// 	{
// 		ft_printf(GREEN"%s\n"ESC, *argv);
// 		argv++;
// 	}
// 	ft_printf(CYAN"%i\n"ESC, argc);
// }