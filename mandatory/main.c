/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:21:26 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/30 20:28:21 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	iterate_through_cmds(t_data *pipex)
{
	int		i;

	dup2(pipex->file_fd[0], STDIN_FILENO);
	close(pipex->file_fd[0]);
	i = 1;
	while (pipex->argv[++i + 1] != NULL)
	{
		split_cmd(pipex, i);
		if (pipe(pipex->pipe_fd) == -1)
			exit_cmd_failed("pipe");
		pipex->pid = fork();
		if (pipex->pid == -1)
			exit_cmd_failed("fork");
		if (pipex->pid == 0)
			process_child(pipex, pipex->argv[i]);
		else
			process_parent(pipex);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;

	if (argc != 5)
		exit_cmd_failed("Invalid number of arguments");
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.file_fd[1] = open(pipex.argv[argc - 1],
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipex.file_fd[1] == -1)
		exit_open_failed(pipex.argv[argc - 1], -1);
	pipex.file_fd[0] = open(pipex.argv[1], O_RDONLY);
	if (pipex.file_fd[0] == -1)
		exit_open_failed(pipex.argv[1], pipex.file_fd[1]);
	iterate_through_cmds(&pipex);
	return (0);
}
