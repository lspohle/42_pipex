/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:39:29 by lspohle           #+#    #+#             */
/*   Updated: 2023/03/21 13:44:50 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_child(t_data pipex)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(pipex.argv[2], ' ');
	if (cmd == NULL)
		display_error(errno);
	cmd_path = get_cmd_path(&pipex, cmd[0]);
	if (cmd_path == NULL)
		display_error(errno);
	dup2(pipex.file_fd[0], 0);
	dup2(pipex.pipe_fd[1], 1);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	execve(cmd_path, cmd, pipex.envp);
}

void	process_parent(t_data pipex)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(pipex.argv[3], ' ');
	if (cmd == NULL)
		display_error(errno);
	cmd_path = get_cmd_path(&pipex, cmd[0]);
	if (cmd_path == NULL)
		display_error(errno);
	dup2(pipex.pipe_fd[0], 0);
	dup2(pipex.file_fd[1], 1);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	execve(cmd_path, cmd, pipex.envp);
	wait(NULL);
}
