/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:39:29 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/22 14:23:01 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_child(t_data pipex)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(pipex.argv[2], ' ');
	if (cmd == NULL)
		display_error(1);
	cmd_path = get_cmd_path(&pipex, cmd[0]);
	if (cmd_path == NULL)
		display_error(127);
	dup2(pipex.file_fd[0], STDIN);
	dup2(pipex.pipe_fd[1], STDOUT);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	if (execve(cmd_path, cmd, pipex.envp) == -1)
		exit(1);
}

void	process_parent(t_data pipex)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(pipex.argv[3], ' ');
	if (cmd == NULL)
		display_error(1);
	cmd_path = get_cmd_path(&pipex, cmd[0]);
	if (cmd_path == NULL)
		display_error(127);
	dup2(pipex.pipe_fd[0], STDIN);
	dup2(pipex.file_fd[1], STDOUT);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	if (execve(cmd_path, cmd, pipex.envp) == -1)
		exit(1);
	wait(NULL);
}
